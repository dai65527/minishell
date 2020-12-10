/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:29:20 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/10 23:22:20 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "minishell.h"
#include <stdio.h>

#define BUFSIZE 1024

static int	get_redirect_fd(char **arg)
{
	int		fd;

	if (**arg == '<')
		return (0);
	if (**arg == '>')
		return (1);
	fd = 0;
	while (ft_isdigit(**arg))
	{
		fd = fd * 10 + **arg - '0';
		(*arg)++;
	}
	return (fd);
}

static int	get_open_option(char *arg)
{
	if (!ft_strncmp(arg, "<", 2))
		return (O_RDONLY);
	else if (!ft_strncmp(arg, ">", 2))
		return (O_WRONLY | O_CREAT);
	else if	(!ft_strncmp(arg, ">>", 3))
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (-1);
}

static int	remove_redirect_from_argv(char **argv)
{
	int		i;

	printf("reach parent reach\n");
	i = 0;
	while (1)
	{
		// free(argv[i]);
		argv[i] = argv[i + 2];
		if (argv[i] == NULL)
			break;
	}
	argv[i + 1] = NULL;
	argv[i + 2] = NULL;
	return (0);
}

int			msh_handle_redirect(char **argv)
{
	int		open_option;
	int		redirect_fd;

	printf("*argv = %s\n", *argv);
	if (*(argv + 1) == NULL)
		return (0);
	if ((redirect_fd = get_redirect_fd(argv)) < 0)
		return (0);
	printf("redirect_fd = %d\n", redirect_fd);
	if ((open_option = get_open_option(*argv)) < 0)
		return (0);
	if (msh_create_redirect_process(*(argv + 1), redirect_fd, open_option) < 0)
		return (-1);
	if (remove_redirect_from_argv(argv) < 0)
		return (-1);
	return (1);
}