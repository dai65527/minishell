/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_floatutil_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:48:02 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:43:17 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_putnaninf(int flag_isnan)
{
	if (flag_isnan)
		ft_putstr_fd("nan", 1);
	else
		ft_putstr_fd("inf", 1);
}

static int		ft_round_check(t_float *iflt, int digit)
{
	int		i;

	if (digit >= 0)
	{
		if (iflt->int_dec[FLT_INTSIZE - (digit + 1)] % 2)
			return (1);
		i = 0;
		while (i < digit - 1)
		{
			if (iflt->int_dec[FLT_INTSIZE - i++ - 1] != 0)
				return (1);
		}
	}
	if (digit < 0 && iflt->mts_dec[-digit - 1] % 2)
		return (1);
	i = digit <= 0 ? -digit + 1 : 0;
	while (i < FLT_MTSSIZE - 1)
	{
		if (iflt->mts_dec[i++] != 0)
			return (1);
	}
	return (0);
}

void			ft_float_round(t_float *iflt, int digit)
{
	if ((digit > FLT_INTSIZE - 1) || (digit < -FLT_MTSSIZE) ||
			(!iflt->frac && iflt->exp == (FLT_EXPBIAS + 1)))
		return ;
	if (digit > 0)
	{
		if (iflt->int_dec[FLT_INTSIZE - digit] > 5)
			ft_float_roundup(iflt, digit);
		else if (iflt->int_dec[FLT_INTSIZE - digit] < 5)
			return ;
		else if (ft_round_check(iflt, digit))
			ft_float_roundup(iflt, digit);
	}
	else
	{
		if (iflt->mts_dec[-digit] > 5)
			ft_float_roundup(iflt, digit);
		else if (iflt->mts_dec[-digit] < 5)
			return ;
		else if (ft_round_check(iflt, digit))
			ft_float_roundup(iflt, digit);
	}
}
