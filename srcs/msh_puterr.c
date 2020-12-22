/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_puterr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:15:46 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/22 16:43:50 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "minishell.h"

/*
** to be modified (issue #8)
** errnoとbashの返り値の関係が謎なので、調べてそれに応じて作り替える。
*/

/*
** Function: msh_puterr
**
** - put error message which is following str1 and str2 to stderr.
** - str1 and str2 will be followed by ": "
** - if str1 (or str2) is null, put nothing for it.
** - simply return 3rd argument "ret".
*/

int			msh_puterr(char *str1, char *str2, int ret)
{
	if (str1)
	{
		ft_putstr_fd(str1, FD_STDERR);
		ft_putstr_fd(": ", FD_STDERR);
	}
	if (str2)
	{
		ft_putstr_fd(str2, FD_STDERR);
		ft_putstr_fd(": ", FD_STDERR);
	}
	ft_putendl_fd(strerror(errno), FD_STDERR);
	return (ret);
}

/*
** Function: msh_puterr_return_null
**
** - put error message as msh_puterr.
** - returns null pointer.
*/

void		*msh_puterr_return_null(char *str1, char *str2)
{
	msh_puterr(str1, str2, 0);
	return (NULL);
}
