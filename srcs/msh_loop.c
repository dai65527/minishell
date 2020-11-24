/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:59:01 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/24 18:21:16 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		msh_loop(t_mshinfo *mshinfo)
{
	int		i;
	int		res_gnl;
	int		res_cmd;
	char	*cmdline;
	char	*cmds;

	while (1)
	{
		if (mshinfo->fd_cmdsrc == 0)
			msh_display_prompt(mshinfo);
		if ((res_gnl = msh_get_next_line(mshinfo->fd_cmdsrc, &cmdline)) < 0)
			return (msh_exit_by_err(mshinfo));
		if (!(cmds = ft_split(cmdline, ';')))
			return (msh_exit_by_err());
		while (cmds[i])
		{
			res_cmd = msh_exec_command(cmds[i++], mshinfo);
			if (res_cmd == MSH_RESCMD_EXIT)
				break;
			i++;
		}
		msh_freelines(cmds);
		if (res_gnl == 0 || res_gnl == 0)
			return (msh_exit_by_cmd(mshinfo));
	}
}
