/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 16:25:41 by dnakano          ###   ########.fr       */
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

static size_t	getkeylen(char *envstr)
{
	size_t	keylen;

	keylen = 0;
	while (envstr[keylen] != '=' && envstr[keylen])
		keylen++;
	return (keylen);
}

static int		export_env(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	size_t		keylen;
	t_keyval	*newenv;
	t_list		*envlst;
	t_list		*newelem;
	int			ret;

	ret = 0;
	while (*(++argv))
	{
		if (!(keylen = getkeylen(*argv)))
		{
			ret = msh_putenverr("export", *argv, 1);
			continue ;
		}
		if (flg_forked || keylen == ft_strlen(*argv))
		{
			if (!msh_env_isvalid(*argv))
				ret = msh_putenverr("export", *argv, 1);
			continue ;
		}
		if (!(newenv = (t_keyval *)malloc(sizeof(t_keyval))))
			return (msh_puterr(MSH_NAME, "env", 1));
		if (!(newenv->key = ft_substr(*argv, 0, keylen))
			|| !(newenv->val = ft_substr(*argv, keylen + 1, ft_strlen(*argv))))
		{
			free(newenv->key);
			free(newenv);
			return (msh_puterr(MSH_NAME, "env", 1));

		}
		if (!msh_env_isvalid(newenv->key))
		{
			msh_keyval_free(newenv);
			ret = msh_putenverr("export", *argv, 1);
			continue ;
		}
		envlst = mshinfo->envlst;
		while (envlst)
		{
			if (!msh_env_cmpkey(newenv, envlst->content))
			{
				msh_free_set(&(((t_keyval *)(envlst->content))->val), newenv->val);
				newenv->val = NULL;
				msh_free_setnull((void *)(&newenv->key));
				msh_free_setnull((void *)(&newenv));
				break ;
			}
			envlst = envlst->next;
		}
		if (newenv)
		{
			if (!(newelem = ft_lstnew(newenv)))
			{
				msh_keyval_free(newenv);
				return (msh_puterr(MSH_NAME, "env", 1));
			}
			ft_lstadd_back(&mshinfo->envlst, newelem);
		}
	}
	return (ret);
}

int				msh_export(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	int		ret;

	if (!argv || !argv[0])
		ret = 1;
	else if (!argv[1])
		ret = sort_and_show_env(mshinfo->envlst);
	else
		ret = export_env(mshinfo, argv, flg_forked);
	ret = 0;
	if (flg_forked)
		exit (ret);
	mshinfo->ret_last_cmd = ret;
	return (0);
}
