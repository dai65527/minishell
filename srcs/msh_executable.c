/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:13:33 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/05 08:43:54 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "minishell.h"

#       include <stdio.h>

/*
**	pipe_locate: location of pipe
*/

int			execute_child(int argc, char **argv, t_mshinfo *mshinfo, int fd_input)
{
	char	**envp;

	(void)argc;
	(void)fd_input;
	if (!(envp = msh_make_envp(mshinfo->envlst)))
		return (MSH_EXIT_BY_ERR);
	execve(argv[0], argv, envp);
	return (MSH_EXIT_BY_ERR);
}

int			msh_executable(int argc, char **argv, t_mshinfo *mshinfo, int fd_input)
{
	int		status;
	pid_t	pid;

	(void)argc;
	if ((pid = fork()) < 0)
		return (MSH_EXIT_BY_ERR);
	else if (pid == 0) /*child process*/
	{
		if (execute_child(argc, argv, mshinfo, fd_input))
			exit (MSH_EXIT_BY_ERR);
	}
	waitpid(pid, &status, 0);
	return (status);
}

# define TEST_MSH_EXECUTABLE
#ifdef TEST_MSH_EXECUTABLE

int		main(int argc, char **argv, char **envp)
{
	t_mshinfo	mshinfo;

	msh_mshinfo_init(&mshinfo);
	if (!(mshinfo.envlst = msh_parse_envp(envp)))
		return (1);
	if (argc <= 1)
		mshinfo.fd_cmdsrc = FD_STDIN;
	return (msh_executable(argc - 1, argv + 1, &mshinfo, 0));
}

#endif
