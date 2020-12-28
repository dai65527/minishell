/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 08:49:16 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/28 13:21:52 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static t_list	*errend(t_list *envlst, t_keyval *env)
{
	if (env)
		msh_keyval_free(env);
	ft_lstclear(&envlst, msh_keyval_free);
	return (NULL);
}

static t_keyval	*get_env_errend(t_keyval *env)
{
	free(env);
	return (msh_puterr_return_null("minshell", NULL));
}

/*
**	Sub function: get_env
**
**	parse one element of envp (envstr) to one element of envlst.
*/

static t_keyval	*get_env(char *envstr)
{
	size_t		keylen;
	t_keyval	*env;

	if (!(env = (t_keyval *)malloc(sizeof(t_keyval))))
		return (msh_puterr_return_null(MSH_NAME, NULL));
	keylen = 0;
	while (envstr[keylen] != '\0' && envstr[keylen] != '=')
		keylen++;
	if (envstr[keylen] == '\0')
		return (get_env_errend(env));
	if (!(env->key = ft_substr(envstr, 0, keylen)))
		return (get_env_errend(env));
	env->val = ft_substr(envstr, keylen + 1, ft_strlen(envstr) - keylen - 1);
	if (!(env->val))
	{
		free(env->key);
		return (get_env_errend(env));
	}
	return (env);
}

/*
**	Function: msh_parse_envp
**
**	Parse and split envp to envlst.
*/

t_list			*msh_parse_envp(char **envp)
{
	t_keyval	*env;
	t_list		*envlst;
	t_list		*newelem;

	envlst = NULL;
	while (*envp)
	{
		if (!(env = get_env(*envp)))
			return (errend(envlst, NULL));
		if (!(newelem = ft_lstnew(env)))
			return (errend(envlst, env));
		ft_lstadd_back(&envlst, newelem);
		envp++;
	}
	return (envlst);
}
