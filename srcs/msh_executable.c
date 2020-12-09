/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:13:33 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/09 18:07:14 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "minishell.h"

pid_t		fork_and_execute(char **argv, t_mshinfo *mshinfo);

int			msh_executable(int argc, char **argv, t_mshinfo *mshinfo, int fd_input)
{
	int		pid;
	int		status;
	int		stdfd_backup[3];
	int		n_pipe_redirect;

	(void)fd_input;
	if (msh_backupfd(stdfd_backup))
		return (MSH_EXIT_BY_ERR);
	if ((n_pipe_redirect = msh_handle_redirect_and_pipe(argv, mshinfo)) < 0)
		return (MSH_EXIT_BY_ERR);
	if ((pid = fork_and_execute(argv, mshinfo)) < -1)
		return (MSH_EXIT_BY_ERR);
	while (n_pipe_redirect-- + 1)
	{
		if (pid == wait(&status))
			mshinfo->ret_last_cmd = status;
	}
	if (msh_resetfd(stdfd_backup))
		return (MSH_EXIT_BY_ERR);
	return (MSH_CONTINUE);
}

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
