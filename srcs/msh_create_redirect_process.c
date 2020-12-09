/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_create_redirect_process.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:29:20 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/09 19:37:51 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"
#include <errno.h>

#define MSH_BUFSIZE 1024

/*
** filediscriptor が有効な範囲かのチェックが未実装
*/

static int	process_write_child(int file_fd, int redirect_fd, int *pipe_fd)
{
	int		len;
	char	buf[MSH_BUFSIZE];

	close(pipe_fd[1]);
	if (redirect_fd < 3)
	{
		while((len = read(pipe_fd[0], buf, MSH_BUFSIZE)) > 0)
			write(file_fd, buf, len);
	}
	close(pipe_fd[0]);
	close(file_fd);
	exit(0);
}

static int	create_redirect_process_write(char *fname,
								int redirect_fd, int open_option)
{
	int		file_fd;
	int		pipe_fd[2];
	int		pid;

	if ((file_fd = open(fname, open_option, 0644)) < 0)
		return (-1);
	if (pipe(pipe_fd) < 0)
	{
		close(file_fd);
		return (-1);
	}
	if ((pid = fork()) < 0)
	{
		msh_closefds(file_fd, pipe_fd);
		return (-1);
	}
	else if (pid == 0)
		process_write_child(file_fd, redirect_fd, pipe_fd);
	if (redirect_fd <= 2)
		dup2(redirect_fd, pipe_fd[1]);
	msh_closefds(file_fd, pipe_fd);
	return (0);
}

static int	create_redirect_process_read(char *fname,
								int redirect_fd, int open_option)
{
	int		file_fd;
	int		pipe_fd[2];
	int		pid;

	if ((file_fd = open(fname, open_option)) < 0)
		return (-1);
	if (pipe(pipe_fd) < 0)
	{
		close(file_fd);
		return (-1);
	}
	if ((pid = fork()) < 0)
	{
		msh_closefds(file_fd, pipe_fd);
		return (-1);
	}
	else if (pid == 0)
		process_write_child(file_fd, redirect_fd, pipe_fd);
	if (redirect_fd <= 2)
		dup2(redirect_fd, pipe_fd[1]);
	msh_closefds(file_fd, pipe_fd);
	return (0);
}

int			open_redirect_file

int			msh_create_redirect_process(char *fname,
								int redirect_fd, int open_option)
{
	int		file_fd;
	int		pipe_fd[2];
	pid_t	pid;

	if (open_option | O_CREAT)
		file_fd = open(fname, open_option, 0644);
	else
		file_fd = open(fname, open_option);
	if (file_fd < 0)
		return (-1);
	if (pipe(pipe_fd) < 0)
	{
		close(file_fd);
		return (-1);
	}
	if ((pid = fork()) < 0)
	{
		msh_closefds(file_fd, pipe_fd);
		return (-1);
	}
	else if (pid == 0)
	{
		if 
	}
	return (0);
}
