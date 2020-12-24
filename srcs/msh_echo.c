/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/20 21:00:43 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				msh_echo(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	(void)mshinfo;
	(void)flg_forked;
	ft_putstr_fd(argv[0], FD_STDOUT);
	ft_putstr_fd(" called\n", FD_STDOUT);
	return (0);
}
