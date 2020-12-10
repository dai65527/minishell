/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_create_redirect_process.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:29:20 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/10 23:59:38 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "minishell.h"
#include <stdio.h>

#define MSH_BUFSIZE 1024

static int	end_create_redirect(int fd, int *pipe_fd, int ret)
{
	msh_closefds(fd, pipe_fd);
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

	printf("reach child\n");
	close(pipe_fd[1]);
	while((len = read(pipe_fd[0], buf, MSH_BUFSIZE)) > 0)
		write(file_fd, buf, len);
	close(pipe_fd[0]);
	close(file_fd);
	printf("reach child\n");
	exit(0);
}

int			msh_create_redirect_process(char *fname,
								int redirect_fd, int open_option)
{
	int		file_fd;
	int		pipe_fd[2];
	pid_t	pid;

	file_fd = open(fname, open_option, 0644);
	if (file_fd < 0)
		return (-1);
	if (pipe(pipe_fd) < 0)
		return (end_create_redirect(file_fd, NULL, -1));
	if ((pid = fork()) < 0)
		return (end_create_redirect(file_fd, pipe_fd, -1));
	else if (pid == 0)
	{
		printf("reach child\n");
		if (open_option | O_WRONLY)
			output_redirect_child(file_fd, pipe_fd);
		else
			input_redirect_child(file_fd, pipe_fd);
	}
	if (redirect_fd <= 2 && (open_option | O_WRONLY))
	{
		dup2(pipe_fd[1], redirect_fd);
	}
	else if (redirect_fd <= 2)
		dup2(pipe_fd[0], redirect_fd);
	return (end_create_redirect(file_fd, pipe_fd, 0));
}
