/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:13:33 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/08 21:43:02 by dnakano          ###   ########.fr       */
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
	int		n_ps;
	int		msh_haspipe;

	(void)fd_input;
	if (msh_backupfd(stdfd_backup))
		return (MSH_EXIT_BY_ERR);
	if ((msh_haspipe = msh_handle_redirect_and_pipe(argv, mshinfo) < 0))
		return (MSH_EXIT_BY_ERR);
	pid = fork_and_execute(argv, mshinfo);
	n_ps = (msh_haspipe == 1) ? 2 : 1;
	while (n_ps--)
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
