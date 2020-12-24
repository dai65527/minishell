/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/24 15:29:05 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void			unset_puterr(const char *envkey)
{
	ft_putstr_fd(MSH_NAME, FD_STDERR);
	ft_putstr_fd(": unset: `", FD_STDERR);
	ft_putstr_fd((char *)envkey, FD_STDERR);
	ft_putstr_fd("': not a valid identifier\n", FD_STDERR);
}

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
		{
			unset_puterr(argv[i]);
			ret = 1;
		}
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
