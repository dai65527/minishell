/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_char_isescaped.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 11:54:12 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/28 12:24:12 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			msh_isescaped(char *s, size_t len_from_start)
{
	int		i;
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
