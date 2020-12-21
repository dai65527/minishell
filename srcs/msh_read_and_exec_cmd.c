/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_read_and_exec_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:02:21 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 15:55:49 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include <stdio.h>		//

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
	int			std_fd[3];
	int			read_fd;
	int			flg_gonext;
	ssize_t		ret;
	char		buf[MSH_READBUFLEN];
	static char	*save;

	if (!save && !(save = ft_strdup("")))
		return (MSH_EXIT_BY_ERR);
	msh_backupfd(std_fd);
	read_fd = (mshinfo->fd_cmdsrc == FD_STDIN) ? std_fd[0] : mshinfo->fd_cmdsrc;
	mshinfo->n_proc = 0;
	while (1)
	{
		if ((ret = read(read_fd, buf, MSH_READBUFLEN)) == 0)
		{
			if (ft_strlen(save) == 0)
				return (MSH_EXIT_BY_CMD);
			else if (mshinfo->fd_cmdsrc == FD_STDIN)
				continue ;
			if (joinbuf(&save, "\n", 1) < 0)
				return (MSH_EXIT_BY_ERR);
		}
		else if (ret < 0)
			return (MSH_EXIT_BY_ERR);
		// write(2, buf, ret);
		if (joinbuf(&save, buf, ret) < 0)
			return (MSH_EXIT_BY_ERR);
		// msh_exec_cmdは\nで終了したら1を返す。エラーは-1。0はもう一度read
		while ((ret = msh_parse_and_exec_cmd(mshinfo, &save, &flg_gonext)) != 0)
		{
			msh_resetfd(std_fd);
			msh_wait(mshinfo, ret);
			if (flg_gonext || ret < 0)
				return (MSH_CONTINUE) ;
		}
	}
}
