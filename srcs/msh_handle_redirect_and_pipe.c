/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_redirect_and_pipe.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:29:20 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/10 23:47:12 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>    

int			msh_handle_redirect_and_pipe(char **argv, t_mshinfo *mshinfo)
{
	int		i;
	int		ret;
	int		n_ps;

	n_ps = 0;
	i = 1;
	while (argv[i])
	{
		if ((ret = msh_handle_redirect(argv + i)) < 0)
			return (-1);
		n_ps += ret;
		if ((ret = msh_handle_pipe(argv + i, mshinfo)) < 0)
			return (-1);
		else if (ret == 1)
			return (n_ps + 1);
		i++;
	}
	return (n_ps);
}
