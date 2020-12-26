/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_value_from_envlst.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:49:51 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/26 14:51:20 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*msh_get_value_from_envlst(t_mshinfo *mshinfo, char **key,
											int flg_quote)
{
	t_list		*head;
	t_keyval	*env;
	char		*invalid_key;

	if (!*key)
	{
		msh_free_setnull((void**)key);
		return (NULL);
	}
	if (!(ft_isalpha(*key[0]) || *key[0] == '_'))
	{
		if (!(invalid_key = ft_strdup("$")))
			return (NULL);
		msh_free_set(&invalid_key, ft_strjoin(invalid_key, *key));
		msh_free_setnull((void**)key);
		return (invalid_key);
	}
	head = mshinfo->envlst;
	while (head)
	{
		env = head->content;
		if (!ft_strncmp(env->key, *key, ft_strlen(*key) + 1))
		{
			msh_free_setnull((void**)key);
			return (env->val);
		}
		head = head->next;
	}
	msh_free_setnull((void**)key);
	if (flg_quote)
		return ("");
	return (NULL);
}
