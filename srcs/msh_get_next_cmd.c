/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_next_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 08:19:31 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/26 15:08:06 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

#define GNC_BUFSIZE 1024

static int	gnc_exit(int ret, char **cmd, char **save)
{
	if (cmd)
	{
		free(*cmd);
		*cmd = NULL;
	}
	if (save)
	{
		free(*save);
		*save = NULL;
	}
	return (ret);
}

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

static int	gnc_continue(t_mshinfo *mshinfo, char **cmd)
{
	(void)mshinfo;
	(void)cmd;
	return (0);
}

int			msh_get_next_cmd(t_mshinfo *mshinfo, char **cmd, char **save)
{
	ssize_t	len;
	char	buf[GNC_BUFSIZE];

	if (!(*save) && !(*save = ft_calloc(1, sizeof(char))))
		return (gnc_exit(MSH_EXIT_BY_ERR, NULL, NULL));
	if (msh_gnc_find_cmd_from_save(cmd, save) == MSH_CONTINUE)
		return (gnc_continue(mshinfo, cmd));
	if (mshinfo->fd_cmdsrc == FD_STDIN)
		ft_putstr_fd(MSH_PROMPT, FD_STDOUT);
	while ((len = read(mshinfo->fd_cmdsrc, buf, GNC_BUFSIZE)) >= 0)
	{
		if (gnc_joinbuf(save, buf, len) != MSH_CONTINUE)
			return (gnc_exit(MSH_EXIT_BY_ERR, cmd, save));
		if (msh_gnc_find_cmd_from_save(cmd, save) == MSH_CONTINUE)
			return (gnc_continue(mshinfo, cmd));
		if (len == 0)
		{
			if (ft_strlen(*save) == 0)
				return (gnc_exit(MSH_EXIT_BY_CMD, cmd, save));
			*cmd = *save;
			*save = NULL;
			return (gnc_continue(mshinfo, cmd));
		}
	}
	return (gnc_exit(MSH_EXIT_BY_CMD, cmd, save));
}
