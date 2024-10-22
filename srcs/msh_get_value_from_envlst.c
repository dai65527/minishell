/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_value_from_envlst.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:49:51 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/28 19:10:08 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int		get_invalid_key(char ***key, char **invalid_key)
{
	if (!(ft_isalpha(**key[0]) || **key[0] == '_'))
	{
		if (!(*invalid_key = ft_strdup("$")))
			return (-1);
		msh_free_set(invalid_key, ft_strjoin(*invalid_key, **key));
		msh_free_setnull((void**)*key);
		return (1);
	}
	return (0);
}

static char		*return_val_free_key(char *ret, char ***key)
{
	free(**key);
	*key = NULL;
	return (ret);
}

char			*msh_get_value_from_envlst(t_mshinfo *mshinfo, char **key,
											int flg_quote)
{
	t_list		*head;
	t_keyval	*env;
	char		*invalid_key;
	char		*val;

	val = NULL;
	if (!*key || !**key)
		return (return_val_free_key(NULL, &key));
	if (get_invalid_key(&key, &invalid_key))
		return (return_val_free_key(invalid_key, &key));
	head = mshinfo->envlst;
	while (head)
	{
		env = head->content;
		if (!ft_strncmp(env->key, *key, ft_strlen(*key) + 1))
		{
			if (!(val = ft_strdup(env->val)))
				return (return_val_free_key(NULL, &key));
			return (return_val_free_key(val, &key));
		}
		head = head->next;
	}
	if (flg_quote && !(val = ft_strdup("")))
		return (return_val_free_key(NULL, &key));
	return (return_val_free_key(val, &key));
}
