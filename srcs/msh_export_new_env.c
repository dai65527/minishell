/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_new_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 16:36:02 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 17:29:31 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static size_t	getkeylen(char *envstr)
{
	size_t	keylen;

	keylen = 0;
	while (envstr[keylen] != '=' && envstr[keylen])
		keylen++;
	return (keylen);
}

static int		arg_isvalid(char *arg)
{
	size_t		keylen;

	if (!(keylen = getkeylen(arg)))
		return (msh_putenverr("export", arg, 0));
	if (keylen == ft_strlen(arg))
	{
		if (!msh_env_isvalid(arg))
			msh_putenverr("export", arg, 0);
		return (0);
	}
	return (1);
}

static t_keyval	*create_newenv(char *arg)
{
	t_keyval	*newenv;
	size_t		keylen;

	keylen = getkeylen(arg);
	if (!(newenv = (t_keyval *)malloc(sizeof(t_keyval))))
		return (msh_puterr_return_null(MSH_NAME, "env"));
	if (!(newenv->key = ft_substr(arg, 0, keylen)))
	{
		free(newenv);
		return (msh_puterr_return_null(MSH_NAME, "env"));
	}
	if (!(newenv->val = ft_substr(arg, keylen + 1, ft_strlen(arg))))
	{
		free(newenv->key);
		free(newenv);
		return (msh_puterr_return_null(MSH_NAME, "env"));
	}
	return (newenv);
}

static int		change_env_val(t_list *envlst, t_keyval *newenv)
{
	while (envlst)
	{
		if (!msh_env_cmpkey(newenv, envlst->content))
		{
			msh_free_set(&(((t_keyval *)(envlst->content))->val), newenv->val);
			newenv->val = NULL;
			msh_free_setnull((void *)(&newenv->key));
			msh_free_setnull((void *)(&newenv));
			return (1);
		}
		envlst = envlst->next;
	}
	return (0);
}

static int		add_new_env(t_mshinfo *mshinfo, t_keyval *newenv)
{
	t_list		*newelem;

	if (!(newelem = ft_lstnew(newenv)))
	{
		msh_keyval_free(newenv);
		return (msh_puterr(MSH_NAME, "env", 1));
	}
	ft_lstadd_back(&mshinfo->envlst, newelem);
	return (0);
}

int				msh_export_new_env(t_mshinfo *mshinfo, char **argv,
															int flg_forked)
{
	t_keyval	*newenv;
	int			ret;

	ret = 0;
	while (*(++argv))
	{
		if (!(arg_isvalid(*argv)) || flg_forked)
		{
			ret = 1;
			continue ;
		}
		if (!(newenv = create_newenv(*argv)))
			return (1);
		if (!msh_env_isvalid(newenv->key))
		{
			msh_keyval_free(newenv);
			ret = msh_putenverr("export", *argv, 1);
			continue ;
		}
		if (change_env_val(mshinfo->envlst, newenv))
			continue ;
		if (add_new_env(mshinfo, newenv))
			return (1);
	}
	return (ret);
}
