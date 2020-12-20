/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_read_and_exec_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:02:21 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/20 20:21:29 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define MSH_READBUFLEN 1024

/*
** readで読み取ったbufをsaveにつなげる
*/

static int	joinbuf(char **save, char *buf, ssize_t len)
{
	ssize_t		save_len;
	char		*save_new;

	save_len = ft_strlen(*save);
	if (!(save_new = (char *)malloc(sizeof(char) * (save_len + len + 1))))
		return (-1);
	ft_strlcpy(save_new, *save, save_len + 1);
	ft_strlcat(save_new, buf, len + save_len + 1);
	free(*save);
	*save = save_new;
	return (0);
}

int			msh_read_and_exec_cmd(t_mshinfo *mshinfo)
{
	int			n_ps;
	int			std_fd[3];
	ssize_t		ret;
	char		buf[MSH_READBUFLEN];
	static char	*save;

	if (!(*save) && !(*save = ft_strdup("")))
		return (MSH_EXIT_BY_ERR);
	msh_backupfd(std_fd);
	mshinfo->n_proc = 0;
	while (1)
	{
		if ((ret = read(mshinfo->fd_cmdsrc, buf, MSH_READBUFLEN)) == 0)
		{
			if (ft_strlen(save) == 0)
				return (MSH_EXIT_BY_CMD);
			else if (mshinfo->fd_cmdsrc == FD_STDIN)
				continue ;
			if (!(save = ft_strjoin(save, "\n")))
				return (MSH_EXIT_BY_ERR);
		}
		else if (ret < 0)
			return (MSH_EXIT_BY_ERR);
		if (joinbuf(&save, buf, ret) < 0)
			return (MSH_EXIT_BY_ERR);
		// msh_exec_cmdは\nで終了したら1を返す。エラーは-1。0はもう一度read
		if ((ret = msh_parse_and_exec_cmd(mshinfo, save)) != 0)
			break ;
	}
	msh_wait(mshinfo, ret);
	msh_resetfd(std_fd);
	return (MSH_CONTINUE);
}
