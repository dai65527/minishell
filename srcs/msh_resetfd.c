/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_resetfd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:12:28 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 18:20:38 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

/*
**	Function: msh_resetfd
**
**	Reset standard file discriptors which were backuped to stdfd[3].
*/

int			msh_resetfd(int *fd_std)
{
	dup2(fd_std[0], FD_STDIN);
	dup2(fd_std[1], FD_STDOUT);
	dup2(fd_std[2], FD_STDERR);
	return (0);
}
