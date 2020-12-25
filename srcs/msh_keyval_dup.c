/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_keyval_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 12:22:06 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 18:05:22 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void		*msh_keyval_dup(void *src_keyval)
{
	t_keyval	*src;
	t_keyval	*dst;

	src = (t_keyval *)src_keyval;
	if (!(dst = (t_keyval *)malloc(sizeof(t_keyval))))
		return (NULL);
	if (!(dst->key = ft_strdup(src->key)))
	{
		free(dst);
		return (NULL);
	}
	if (!(dst->val = ft_strdup(src->val)))
	{
		free(dst->key);
		free(dst);
		return (NULL);
	}
	return ((void *)dst);
}
