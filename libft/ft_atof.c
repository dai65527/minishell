/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:42:08 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/30 19:31:10 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atof.h"

double	ft_atof(const char *s)
{
	t_float		iflt;

	ft_atof_atobin(s, &iflt);
	return (ft_atof_bintof(iflt));
}
