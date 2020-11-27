/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free_setnull.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:39:02 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/11/26 13:39:59 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	msh_free_setnull(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
