/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_create_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:29:20 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 13:44:08 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "minishell.h"
#include <stdio.h>

#define MSH_BUFSIZE 1024

static int	close_end(int file_fd, int pipe_fd[2], int ret)
{
	if (file_fd >= 0)
		close(file_fd);
	if (pipe_fd)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	return (ret);
}

static int	input_redirect_child(int file_fd, int *pipe_fd)
{
	int		len;
	char	buf[MSH_BUFSIZE];

	close(pipe_fd[0]);
	while((len = read(file_fd, buf, MSH_BUFSIZE)) > 0)
		write(pipe_fd[1], buf, len);
	close(pipe_fd[1]);
	close(file_fd);
	exit(0);
}

static int	output_redirect_child(int file_fd, int *pipe_fd)
{
	int		len;
	char	buf[MSH_BUFSIZE];

	close(pipe_fd[1]);
	while((len = read(pipe_fd[0], buf, MSH_BUFSIZE)) > 0)
		write(file_fd, buf, len);
	close(pipe_fd[0]);
	close(file_fd);
	exit(0);
}


static int	open_redirect_file(char *fname, int flg_redirect)
{
	int		fd;

	if (flg_redirect == 0)
		fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (flg_redirect == 1)
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (msh_puterr(fname, -1));
	return (fd);
}

/*
** return value
**	-1: error occured
**	 0: no process created
**	 1: one process created
*/

int			msh_create_redirect(char *fname, int redirect_fd,
									int flg_redirect)
{
	int		file_fd;
	int		pipe_fd[2];
	pid_t	pid;

	if (redirect_fd > 2 || redirect_fd < 0)
		return (0);
	if ((file_fd = open_redirect_file(fname, flg_redirect)) < 0)
		return (-1);
	if (pipe(pipe_fd) < 0)
		return (close_end(file_fd, NULL, -1));
	if ((pid = fork()) < 0)
		return (close_end(file_fd, pipe_fd, -1));
	else if (pid == 0)
	{
		if (flg_redirect == 2)
			input_redirect_child(file_fd, pipe_fd);
		else
			output_redirect_child(file_fd, pipe_fd);
	}
	if (flg_redirect == 2)
		dup2(pipe_fd[0], redirect_fd);
	else
		dup2(pipe_fd[1], redirect_fd);
	return (close_end(file_fd, pipe_fd, 1));
}
