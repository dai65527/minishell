/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/24 12:19:57 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void		msh_putenv(t_list *envlst)
{
	t_keyval	*env;

	while (envlst)
	{
		env = (t_keyval *)envlst->content;
		ft_putstr_fd(env->key, FD_STDOUT);
		ft_putstr_fd("=", FD_STDOUT);
		ft_putendl_fd(env->val, FD_STDOUT);
		envlst = envlst->next;
	}
}

int				msh_env(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	int		ret;

	if (argv[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", FD_STDERR);
		ret = 2;
	}
	else
		msh_putenv(mshinfo->envlst);
	if (flg_forked)
		exit((unsigned char)ret);
	mshinfo->ret_last_cmd = (unsigned char)ret;
	return (0);
}
