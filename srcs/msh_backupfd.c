/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_backupfd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:12:28 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/20 13:45:54 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

/*
** msh_backupfd
**
**	Backup original standard fds (stdin, stdout, stderr) to stdfd_backup.
**  This is needed because these might be overwritten by pipefd.
*/

int			msh_backupfd(int stdfd_backup[3])
{
	stdfd_backup[0] = dup(FD_STDIN);
	stdfd_backup[1] = dup(FD_STDOUT);
	stdfd_backup[2] = dup(FD_STDERR);
	return (0);
}
