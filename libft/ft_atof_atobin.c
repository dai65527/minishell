/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_atobin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:34:47 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/30 19:32:44 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atof.h"

static void	init_ifloat(t_float *iflt)
{
	iflt->sign = 0;
	iflt->exp = 0;
	iflt->frac = 0;
	iflt->exp_d = 0;
	uint128_bzero(&(iflt->frac_d));
}

void		ft_atof_atobin(const char *s, t_float *iflt)
{
	init_ifloat(iflt);
	ft_atof_atodec(s, iflt);
	ft_atof_dectobin_exp(iflt);
	ft_atof_dectobin_frac(iflt);
}
