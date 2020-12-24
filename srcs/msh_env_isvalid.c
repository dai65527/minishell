/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_isvalid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:15:43 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/24 14:23:20 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
**	Function: msh_env_isvalid
**
**	This function checks if the argument string is valid as key of environment
**	variable.
**	A key of enviroment variable must consit of only alphabet , underbar or
**	digit charactor but it must not be started by digit.
**	Returns 1 if valid and 0 if not.
*/

int			msh_env_isvalid(const char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	while (*(++key))
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
	}
	return (1);
}
