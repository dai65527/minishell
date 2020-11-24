/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_keyval_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:50:19 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/24 19:54:58 by dnakano          ###   ########.fr       */
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

void	msh_keyval_free(t_keyval *keyval)
{
	free(keyval->key);
	keyval->key = NULL;
	free(keyval->val);
	keyval->val = NULL;
	free(keyval);
}
