/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_next_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 08:19:31 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/18 12:01:39 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

#define GNC_BUFSIZE 1024

/*
** msh_get_next_cmd終了時の後処理。
** exitの表示もここで行う。
*/

static int	gnc_exit(int ret, char **cmd, char **save)
{
	if (cmd)
		msh_free_setnull((void **)cmd);
	if (save)
		msh_free_setnull((void **)save);
	if (ret == MSH_EXIT_BY_CMD)
		ft_putendl_fd("exit", FD_STDOUT);
	return (ret);
}

/*
** readで読み取ったbufをsaveにつなげる
*/

static int	gnc_joinbuf(char **save, char *buf, ssize_t len)
{
	ssize_t		save_len;
	char		*save_new;

	save_len = ft_strlen(*save);
	if (!(save_new = (char *)malloc(sizeof(char) * (save_len + len + 1))))
		return (!MSH_CONTINUE);
	ft_strlcpy(save_new, *save, save_len + 1);
	ft_strlcat(save_new, buf, len + save_len + 1);
	free(*save);
	*save = save_new;
	return (MSH_CONTINUE);
}

/*
** msh_get_next_cmd
**
** DESCRIPTION
** mshinfo->fd_cmdsrc から文字列を読み取り、
** '\n' or ';' で区切られるコマンド抽出する。
** 抽出されたコマンドをcmdに格納し、
** 残りの文字列をsaveに格納する。
** 読み取り中にEOFがあれば読み取りを終了する。
** 標準入力からの読み取りであれば、入力待機時にコンソールを出力し、終了時にexitと出力する
**
** RETURN VALUE
** MSH_CONTINUE: コマンドが読み取られた時。
** MSH_EXIT_BY_CMD: EOFが入力された場合。
** MSH_EXIT_BY_ERR: 何らかのエラー（malloc失敗）等があった場合。
**
** ISSUE
** #13 Ctrl+D Ctrl+Cの挙動
*/

int			msh_exec_next_cmd(t_mshinfo *mshinfo, char **cmd, char **save)
{
	ssize_t	len;
	char	buf[GNC_BUFSIZE];

	if (!(*save) && !(*save = ft_calloc(1, sizeof(char))))
		return (gnc_exit(MSH_EXIT_BY_ERR, NULL, NULL));
	if (msh_find_cmd_and_exec(cmd, save) != MSH_CONTINUE)
		return (*save ? MSH_CONTINUE : MSH_EXIT_BY_ERR);
	if (mshinfo->fd_cmdsrc == FD_STDIN)
		ft_putstr_fd(MSH_PROMPT, FD_STDOUT);
	while ((len = read(mshinfo->fd_cmdsrc, buf, GNC_BUFSIZE)) >= 0)
	{
		if (gnc_joinbuf(save, buf, len) != MSH_CONTINUE)
			return (gnc_exit(MSH_EXIT_BY_ERR, cmd, save));
		if (msh_gnc_find_cmd_from_save(cmd, save) != MSH_CONTINUE)
			return (*save ? MSH_CONTINUE : MSH_EXIT_BY_ERR);
		if (len < GNC_BUFSIZE)
		{
			if (ft_strlen(*save) == 0)
				return (gnc_exit(MSH_EXIT_BY_CMD, cmd, save));
			*cmd = *save;
			*save = NULL;
			return (MSH_CONTINUE);
		}
	}
	return (gnc_exit(MSH_EXIT_BY_CMD, cmd, save));
}
