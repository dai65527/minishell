/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 21:01:44 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/28 12:35:14 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

void		msh_wait(t_mshinfo *mshinfo, pid_t pid)
{
	int		status;

	while (mshinfo->n_proc > 0)
	{
		if (wait(&status) == pid)
			mshinfo->ret_last_cmd = WIFSIGNALED(status) ?
										status + 128 : WEXITSTATUS(status);
		mshinfo->n_proc--;
	}
}
