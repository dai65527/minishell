/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_redirect_and_pipe.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:29:20 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/09 18:02:42 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			msh_handle_redirect_and_pipe(char **argv, t_mshinfo *mshinfo)
{
	int		i;
	int		haspipe;
	int		ret;
	int		n_ps;

	i = 1;
	while (argv[i + 1])
	{
		if ((ret = msh_handle_redirect(argv + i)) < 0)
			return (-1);
		n_ps += ret;
		if ((haspipe = handle_pipe(argv)) < 0)
			return (-1);
		else if (haspipe == 1)
			return (n_ps + 1);
		i++;
	}
	return (n_ps);
}
