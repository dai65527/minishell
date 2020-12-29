/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_isescaped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 11:54:12 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/29 21:02:14 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	function: msh_isescaped
**
**	check if the *s is escaped by '\'.
**	len_from_start means pointer s is at len_from_start'th place from start of
**	the string.
**	*s is escaped if odd numbers of '\' is placed just before the *s.
*/

int			msh_isescaped(char *s, size_t len_from_start)
{
	size_t	i;
	int		flg_isescaped;

	flg_isescaped = 0;
	i = 1;
	while (i <= len_from_start && *(s - i) == '\\')
	{
		flg_isescaped = !flg_isescaped;
		i++;
	}
	return (flg_isescaped);
}
