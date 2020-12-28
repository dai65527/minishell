/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 16:01:41 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int				msh_unset(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	int			i;
	int			ret;
	t_keyval	env;

	ret = 0;
	i = 1;
	while (argv[i])
	{
		if (!msh_env_isvalid(argv[i]))
			ret = msh_putenverr("unset", argv[i], 1);
		else if (!mshinfo->has_pipe)
		{
			env.key = argv[i];
			ft_lstrm_if(&(mshinfo->envlst), &env, msh_env_cmpkey,
				msh_keyval_free);
		}
		i++;
	}
	if (flg_forked)
		exit(ret);
	mshinfo->ret_last_cmd = ret;
	return (0);
}
