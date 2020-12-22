/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_mshinfo_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:38:44 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 18:01:51 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "minishell.h"

/*
** Function: msh_mshinfo_init
**
** Initialize structure mshinfo which stores information needed by working
** minishell. For detail of mshinfo, refer to minishell.h.
*/

int		msh_mshinfo_init(t_mshinfo *mshinfo)
{
	if ((mshinfo->fd_std[0] = dup(FD_STDIN)) < 0)
		return (msh_puterr("minishell", NULL, errno));
	if ((mshinfo->fd_std[1] = dup(FD_STDOUT)) < 0)
	{
		close(mshinfo->fd_std[0]);
		return (msh_puterr("minishell", NULL, errno));
	}
	if ((mshinfo->fd_std[2] = dup(FD_STDERR)) < 0)
	{
		close(mshinfo->fd_std[0]);
		close(mshinfo->fd_std[1]);
		return (msh_puterr("minishell", NULL, errno));
	}
	mshinfo->envlst = NULL;
	mshinfo->arglst = NULL;
	mshinfo->n_proc = 0;
	mshinfo->fd_cmdsrc = 0;
	mshinfo->ret_last_cmd = 0;
	return (0);
}
