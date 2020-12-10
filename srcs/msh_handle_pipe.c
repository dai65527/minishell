/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:49:56 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/10 23:54:15 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "minishell.h"
#include  <stdio.h>

int			msh_handle_pipe(char **argv, t_mshinfo *mshinfo)
{
	int		pipe_fd[2];
	pid_t	pid;

	printf("reach\n");
	if (!argv[0] || ft_strncmp(argv[0], "|", 2) || argv[1] == NULL)
		return (0);
	if (pipe(pipe_fd) < 0)
		return (-1);
	if ((pid = fork()) < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (0);
	}
	else if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], FD_STDIN);
		close(pipe_fd[0]);
		msh_exec_cmd(mshinfo, argv);
		exit(errno);
	}
	return (1);
}
