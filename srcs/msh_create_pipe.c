/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_create_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:49:56 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 07:51:31 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

pid_t		msh_create_pipe(t_mshinfo *mshinfo, char **argv)
{
	int		pipe_fd[2];
	pid_t	pid;

	pipe(pipe_fd);
	if ((pid = fork()) < 0)
		return (-1);
	else if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		msh_exec_cmd(mshinfo, argv, 1);
		exit(1);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	mshinfo->n_proc++;
	return (pid);
}
