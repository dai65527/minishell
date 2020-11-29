/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 08:49:16 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/29 11:20:58 by dnakano          ###   ########.fr       */
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
	return (NULL);
}

static t_keyval	*get_env(char *envstr)
{
	size_t		keylen;
	t_keyval	*env;

	ft_printf("%s\n", envstr);
	if (!(env = (t_keyval *)malloc(sizeof(t_keyval))))
		return (NULL);
	keylen = 0;
	while (envstr[keylen] != '\0' && envstr[keylen] != '=')
		keylen++;
	if (envstr[keylen] == '\0')
		return (get_env_errend(env));
	if (!(env->key = ft_substr(envstr, 0, keylen)))
		return (get_env_errend(env));
	if (!(env->val = ft_substr(envstr, keylen + 1, ft_strlen(envstr) - keylen - 1)))
	{
		free(env->key);
		return (get_env_errend(env));
	}
	return (env);
}

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

#ifdef TEST

int		main(int argc, char **argv, char **envp)
{
	t_mshinfo	mshinfo;
	t_list		*envlst;

	(void)argc;
	(void)argv;
	msh_mshinfo_init(&mshinfo);
	if (!(mshinfo.envlst = msh_parse_envp(envp)))
		return (1);
	envlst = mshinfo.envlst;
	while (envlst)
	{
		ft_printf("key = \"%s\", val = \"%s\"\n", ((t_keyval *)(envlst->content))->key, ((t_keyval *)(envlst->content))->val);
		envlst = envlst->next;
	}
	msh_mshinfo_free(&mshinfo);
	return (0);
}

#endif
