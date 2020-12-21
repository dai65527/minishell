/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_resetfd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:12:28 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 15:53:42 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

/*
** msh_resetfd
**
**	reset standard file discriptors which were backuped to stdfd_backup[3] in
**	msh_backupfd function. Must close stdfd_backup after they were duplicated.
*/

int			msh_resetfd(int *stdfd_backup)
{
	dup2(stdfd_backup[0], FD_STDIN);
	dup2(stdfd_backup[1], FD_STDOUT);
	dup2(stdfd_backup[2], FD_STDERR);
	return (0);
}
