/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_cmpkey.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:03:44 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/29 19:35:22 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Function: msh_env_cmpkey.c
**
**	Compare key of envlst by ft_strcmp to 1st argument and return the result.
*/

#include "minishell.h"

int			msh_env_cmpkey(void *env1, void *env2)
{
	return (ft_strncmp(((t_keyval *)env1)->key, ((t_keyval *)env2)->key,
				ft_strlen(((t_keyval *)env1)->key) + 1));
}
