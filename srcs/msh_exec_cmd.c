/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:42:10 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/29 20:49:09 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
** handling empty argv
*/

static int	emptyargv(t_mshinfo *mshinfo, int flg_forked)
{
	if (flg_forked)
		exit(0);
	mshinfo->ret_last_cmd = 0;
	return (0);
}

int			msh_exec_cmd(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	if (!argv[0])
		return (emptyargv(mshinfo, flg_forked));
	if (!msh_strcmp_inlower(argv[0], "echo"))
		return (msh_echo(mshinfo, argv, flg_forked));
	else if (!ft_strncmp(argv[0], "cd", 3))
		return (msh_cd(mshinfo, argv, flg_forked));
	else if (!msh_strcmp_inlower(argv[0], "pwd"))
		return (msh_pwd(mshinfo, flg_forked));
	else if (!ft_strncmp(argv[0], "export", 7))
		return (msh_export(mshinfo, argv, flg_forked));
	else if (!ft_strncmp(argv[0], "unset", 6))
		return (msh_unset(mshinfo, argv, flg_forked));
	else if (!msh_strcmp_inlower(argv[0], "env"))
		return (msh_env(mshinfo, argv, flg_forked));
	else if (!ft_strncmp(argv[0], "exit", 5))
		return (msh_exit(mshinfo, argv, flg_forked));
	return (msh_executable(mshinfo, argv, flg_forked));
}
