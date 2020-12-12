/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_value_from_envlst.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:49:51 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/12 02:49:56 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include "minishell.h"

char			*get_value_from_envlst(t_mshinfo *mshinfo, char **key)
{
	t_list		*head;
	t_keyval	*env;

	if (!*key)
	{
		msh_free_setnull((void**)key);
		return ("");
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
	return ("");
}
