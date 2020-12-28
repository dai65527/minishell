/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:13:33 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/28 13:09:15 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include "minishell.h"

#define BUFSIZE 2048

static int		execute(t_mshinfo *mshinfo, char **argv, const char *path)
{
	char		**envp;

	if (!(envp = msh_make_envp(mshinfo->envlst)))
		exit(errno);
	execve(path, argv, envp);
	exit(msh_puterr(MSH_NAME, argv[0], errno));
}

int				msh_executable(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	pid_t	pid;
	char	path[PATH_MAX];

	if (msh_find_and_copy_path(argv, mshinfo, path) < 0)
	{
		mshinfo->ret_last_cmd = 127;
		return (-1);
	}
	if (flg_forked)
		execute(mshinfo, argv, path);
	if ((pid = fork()) < 0)
	{
		mshinfo->ret_last_cmd = 1;
		return (msh_puterr(MSH_NAME, "fork", 0));
	}
	else if (pid == 0)
		execute(mshinfo, argv, path);
	mshinfo->n_proc++;
	return (pid);
}
