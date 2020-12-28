/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:32:31 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/28 13:02:15 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	msh_free_set(char **dest, char *src)
{
	free(*dest);
	*dest = src;
}

void	msh_free_argvp(void ***argvp)
{
	int i;

	i = 0;
	while ((*argvp)[i])
	{
		msh_free_setnull(&((*argvp)[i]));
		i++;
	}
	msh_free_setnull((void **)argvp);
	*argvp = NULL;
}
