/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_isenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 11:23:28 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/28 11:23:59 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			msh_isenv(char *s, char *envkey, size_t slen)
{
	return (ft_strncmp(s, envkey, slen) && ft_strlen(envkey) == slen);
}
