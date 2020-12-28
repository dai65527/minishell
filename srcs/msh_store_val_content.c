/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_store_val_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:52:36 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/27 15:19:58 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t			msh_store_val_content(char **val, char **content)
{
	if (*content && *val)
		msh_free_set(content, ft_strjoin(*content, *val));
	else if (*val)
		*content = ft_strdup(*val);
	else
		return (0);
	if (!*content)
		return (-1);
	msh_free_setnull((void**)val);
	return (0);
}
