/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/20 20:57:47 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				msh_pwd(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	(void)mshinfo;
	(void)flg_forked;
	ft_putstr_fd(argv[0], FD_STDOUT);
	ft_putstr_fd(" called\n", FD_STDOUT);
	return (0);
}
