/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/23 02:01:08 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				msh_echo(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	int	flg_omit_newline;
	int	i;

	(void)flg_forked;
	if (!argv[1])
	{
		ft_putstr_fd("\n", FD_STDOUT);
		mshinfo->ret_last_cmd = 0;
		return (0);
	}
	flg_omit_newline = (!ft_strncmp(argv[1], "-n", 3)) ? 1 : 0;
	i = 0;
	while (argv[++i + flg_omit_newline])
	{
		if (i != 1)
			ft_putstr_fd(" ", FD_STDOUT);
		ft_putstr_fd(argv[i + flg_omit_newline], FD_STDOUT);
	}
	if (!flg_omit_newline)
		ft_putstr_fd("\n", FD_STDOUT);
	mshinfo->ret_last_cmd = 0;
	return (0);
}
