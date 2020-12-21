/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_puterr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:15:46 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 06:50:08 by dnakano          ###   ########.fr       */
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
** msh_ext_by_err
**
** for in case minishell itself encounters an error.
** minishell自体がエラーに遭遇したときに終了する用
*/

int			msh_puterr(char *str, int ret)
{
	if (str)
		ft_putstr_fd(str, FD_STDERR);
	else
		ft_putstr_fd("bash", FD_STDERR);
	ft_putstr_fd(": ", FD_STDERR);
	ft_putendl_fd(strerror(errno), FD_STDERR);
	return (ret);
}
