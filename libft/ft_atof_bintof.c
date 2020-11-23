/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_bintof.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:35:59 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/30 19:29:41 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atof.h"

double	ft_atof_bintof(t_float iflt)
{
	t_ufloat	ufloat;

	ufloat.mem = 0;
	ufloat.mem |= ((uint64_t)iflt.sign << 63);
	ufloat.mem |= ((uint64_t)iflt.exp << 52);
	ufloat.mem |= iflt.frac;
	return (ufloat.num);
}
