/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:13:33 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/11 11:30:00 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include "minishell.h"

static pid_t	fork_and_execute(char **argv, t_mshinfo *mshinfo)
{
	pid_t	pid;
	char	**envp;
	char	path[PATH_MAX];

	if (msh_find_and_copy_path(argv, mshinfo, path) < 0)
	{
		mshinfo->ret_last_cmd = 127;
		return (-1);
	}
	if ((pid = fork()) < 0)
		return (-1);
	else if (pid == 0)	
	{
		if (!(envp = msh_make_envp(mshinfo->envlst)))
			return (-1);
		execve(path, argv, envp);
		exit(errno);
	}
	return (0);
}

int				msh_executable(char **argv, t_mshinfo *mshinfo)
{
	int		pid;
	int		status;
	int		stdfd_backup[3];
	int		n_ps;

	if (msh_backupfd(stdfd_backup))
		return (MSH_EXIT_BY_ERR);
	if ((n_ps = msh_handle_redirect_and_pipe(argv, mshinfo)) < 0)
		return (MSH_EXIT_BY_ERR);
	if ((pid = fork_and_execute(argv, mshinfo)) != -1)
		n_ps++;
	msh_resetfd(stdfd_backup);
	while (n_ps--)
	{
		if (pid == wait(&status))
			mshinfo->ret_last_cmd = status;
	}
	return (MSH_CONTINUE);
}

/*
**	HOW TO TEST
**
**	0.	move to srcs directory.
**	1.	compile with -- gcc -Wall -Wextra -Werror -D TEST_MSH_EXECUTABLE -I../includes msh_executable.c msh_handle_redirect_and_pipe.c msh_handle_redirect.c msh_create_redirect_process.c msh_handle_pipe.c msh_find_and_copy_path.c msh_backupfd.c msh_resetfd.c msh_closefds.c msh_mshinfo_init.c msh_parse_envp.c msh_make_envp.c msh_keyval_free.c ../libft/libft.a
**	2.	it works with command line arguments. ( '>', '<' or '|' should be escaped)
**	ex)
**		$ ./a.out cat
**		$ ./a.out cat test.txt
**		$ ./a.out cat test.txt \> test2.txt
**		$ ./a.out cat test.txt \>\> test2.txt
**		$ ./a.out cat test.txt \> test2.txt \> test3.txt
**		$ ./a.out cat \< test.txt \> test2.txt
**		$ ./a.out ls | cat
**		$ ./a.out ls | cat 
*/

#ifdef TEST_MSH_EXECUTABLE

#include <stdio.h>

int		msh_exec_cmd(t_mshinfo *mshinfo, char **argv)
{
	return (msh_executable(argv, mshinfo));
}

int		main(int argc, char **argv, char **envp)
{
	t_mshinfo	mshinfo;

	printf("start\n");
	if (argc == 1)
		return (1);
	msh_mshinfo_init(&mshinfo);
	if (!(mshinfo.envlst = msh_parse_envp(envp)))
		return (1);
	if (argc <= 1)
		mshinfo.fd_cmdsrc = FD_STDIN;
	msh_executable(argv + 1, &mshinfo);
	printf("end\n");
	return (0);
}

#endif
