/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_keyval_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 12:22:06 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 12:46:46 by dnakano          ###   ########.fr       */
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

#ifdef TEST_KEYVAL_DUP

#include <stdio.h>

int			main(void)
{
	t_keyval	src;
	t_keyval	*dst;

	src.key = ft_strdup("42");
	src.val = ft_strdup("tokyo");
	dst = msh_keyval_dup(&src);
	printf("src: %s = %s\n", src.key, src.val);
	printf("dst: %s = %s\n", dst->key, dst->val);
	free(src.key);
	free(src.val);
	msh_keyval_free(dst);
	return (0);
}

#endif
