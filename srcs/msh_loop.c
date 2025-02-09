/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:59:01 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/28 18:55:52 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "minishell.h"

/*
**	Function: msh_loop
**
**	- Put script if command source is standard input.
**	- If return value of msh_read_and_exec_cmd is not 0, quit main loop.
**	- Put message "exit" when exiting properly. (Return value of
**	  msh_read_and_exec_cmd is 1)
**	- Returns...
**		- 0 on proper termination of minishell.
**		- -1 when some error has occured.
*/

int		msh_loop(t_mshinfo *mshinfo)
{
	int		ret;

	while (1)
	{
		if (msh_initsignal() < 0)
			return ((msh_puterr(MSH_NAME, NULL, errno)));
		ft_putstr_fd(MSH_PROMPT, FD_STDERR);
		if ((ret = msh_read_and_exec_cmd(mshinfo)) != 0)
			break ;
	}
	if (ret < 0)
		return (-1);
	ft_putstr_fd("exit\n", FD_STDERR);
	return (0);
}
