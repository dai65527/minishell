/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 17:21:17 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void		showenv(void *env)
{
	ft_putstr_fd("declare -x ", FD_STDOUT);
	ft_putstr_fd(((t_keyval *)env)->key, FD_STDOUT);
	ft_putstr_fd("=\"", FD_STDOUT);
	ft_putstr_fd(((t_keyval *)env)->val, FD_STDOUT);
	ft_putstr_fd("\"\n", FD_STDOUT);
}

static int		sort_and_show_env(t_list *envlst)
{
	t_list		*envlst_cp = envlst;

	if (!(envlst_cp = ft_lstdup(envlst, msh_keyval_dup, msh_keyval_free)))
		return (msh_puterr(MSH_NAME, "export", 1));
	ft_lstsort(&envlst_cp, msh_env_cmpkey);
	ft_lstiter(envlst_cp, showenv);
	ft_lstclear(&envlst_cp, msh_keyval_free);
	return (0);
}

int				msh_export(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	int		ret;

	if (!argv || !argv[0])
		ret = 1;
	else if (!argv[1])
		ret = sort_and_show_env(mshinfo->envlst);
	else
		ret = msh_export_new_env(mshinfo, argv, flg_forked);
	if (flg_forked)
		exit (ret);
	mshinfo->ret_last_cmd = ret;
	return (0);
}
