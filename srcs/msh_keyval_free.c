/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_keyval_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:50:19 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/25 10:39:26 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*
** msh_keyval_free
**
** free struct t_keyval.
** t_keyval構造体のフリー用関数
*/

void	msh_keyval_free(void *keyval)
{
	free(((t_keyval *)keyval)->key);
	((t_keyval *)keyval)->key = NULL;
	free(((t_keyval *)keyval)->val);
	((t_keyval *)keyval)->val = NULL;
	free(keyval);
}
