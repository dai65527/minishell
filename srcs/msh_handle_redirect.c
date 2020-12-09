/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:29:20 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/09 17:55:16 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"
#include <errno.h>

#define BUFSIZE 1024

/*
** filediscriptor が有効な範囲かのチェックが未実装
** 現在は3以上は何もせずスルーする。
*/

static int	get_redirect_fd(const char **arg)
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
	int		open_option;

	if (!ft_strncmp(arg, "<", 2))
		return (O_WRONLY | O_CREAT);
	else if (!ft_strncmp(arg, ">", 2))
		return (O_WRONLY | O_CREAT | O_APPEND);
	else if	(!ft_strncmp(arg, ">>", 3))
		return (O_RDONLY);
	return (-1);
}

int			msh_handle_redirect(const char **argv)
{
	int		open_option;
	int		redirect_fd;
	int		file_fd;

	if ((redirect_fd = get_redirect_fd(argv)) < 0)
		return (0);
	if ((open_option = get_open_option(*argv)) < 0)
		return (0);
	if (msh_create_redirect_process(*(argv + 1), redirect_fd, open_option) < 0)
		return (-1);
	if (remove_redirect_from_argv(argv) < 0)
		return (-1);
	return (1);
}
