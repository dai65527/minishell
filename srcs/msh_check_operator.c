/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_check_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:48:07 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/17 01:21:09 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** check are there special character(operator) and are they escaped
*/

int				msh_check_operator(char *save, ssize_t len, char *operator)
{
	if (save[len] && !(ft_strchr(operator, save[len])
		&& !msh_isescaped(&save[len], len)))
		return (1);
	else
		return (0);
}
