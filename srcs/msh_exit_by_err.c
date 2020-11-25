/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit_by_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:15:46 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/25 07:27:39 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "minishell.h"

/*
** to be modified (issue #8)
** errnoとbashの返り値の関係が謎なので、調べてそれに応じて作り替える。
*/

static int	exit_by_err_returnval(void)
{
	return (errno);
}

/*
** msh_ext_by_err
**
** for in case minishell itself encounters an error.
** minishell自体がエラーに遭遇したときに終了する用
*/

int			msh_exit_by_err(t_mshinfo *mshinfo)
{
	msh_put_errmsg(mshinfo);
	msh_mshinfo_free(mshinfo);
	return (exit_by_err_returnval());
}
