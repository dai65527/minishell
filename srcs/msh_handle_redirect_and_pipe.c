/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_redirect_and_pipe.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:29:20 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/09 09:26:22 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

#define REDIRECT_WRITE (O_WRONLY | O_CREAT)
#define REDIRECT_ADD (REDIRECT_WRITE | O_APPEND)
#define REDIRECT_READ O_RDONLY

static int	get_redirect_fd(const char **arg)
{
	int		fd;

	fd = 0;
	while (ft_isdigit(**arg))
	{
		fd = fd * 10 + **arg - '0';
		(*arg)++;
	}
	return (fd);
}

static int	handle_redirect(const char **argv)
{
	int		open_option;
	int		redirect_fd;
	int		file_fd;

	redirect_fd = get_redirect_fd(argv);
	if (!ft_strncmp(*argv, "<", 2))
		open_option = REDIRECT_READ;
	else if (!ft_strncmp(*argv, ">", 2))
		open_option = REDIRECT_WRITE;
	else if	(!ft_strncmp(*argv, ">>", 3))
		open_option = REDIRECT_ADD;
	else
		return (0);
	if (open_option | O_CREAT)
	{
		file_fd = open(argv + 1, open_option, 0644);
		create_redirect_pipe(redirect_fd, file_fd, 'w');
	}
	else
	{
		file_fd = open(argv + 1, open_option);
		create_redirect_pipe(redirect_fd, file_fd, 'r');
	}
	remove_redirect_from_argv(argv);
	return (1);
}

int			msh_handle_redirect_and_pipe(char **argv, t_mshinfo *mshinfo)
{
	int		i;
	int		haspipe;

	i = 1;
	while (argv[i + 1])
	{
		if (handle_redirect(argv + i) < 0)
			return (-1);
		if ((haspipe = handle_pipe(argv)) < 0)
			return (-1);
		else if (haspipe == 1)
			return (haspipe);
		i++;
	}
	return (0);
}
