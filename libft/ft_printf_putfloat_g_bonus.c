/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putfloat_g_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:36:42 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:43:05 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_putinstyle_f(t_float iflt, t_printf_flags *flags)
{
	int				e;
	const t_float	iflt_o = iflt;

	e = ft_printf_putfloat_e_get(iflt, flags);
	if (flags->precision >= e + 1)
		flags->precision -= (e + 1);
	if (flags->flag & FLAG_ALTERNATE)
		return (ft_printf_putfloat_f(iflt_o, flags));
	if (flags->precision >= FLT_MTSSIZE)
		flags->precision = FLT_MTSSIZE - 1;
	ft_float_round(&iflt, -flags->precision);
	while (flags->precision > 0 && !iflt.mts_dec[flags->precision - 1])
		flags->precision--;
	return (ft_printf_putfloat_f(iflt_o, flags));
}

static int		ft_putinstyle_e(t_float iflt, t_printf_flags *flags, int e)
{
	const t_float	iflt_o = iflt;

	flags->precision--;
	if (flags->flag & FLAG_ALTERNATE)
		return (ft_printf_putfloat_e(iflt_o, flags));
	if (flags->precision - e >= FLT_MTSSIZE)
		flags->precision = FLT_MTSSIZE + e - 1;
	ft_float_round(&iflt, e - flags->precision);
	while (flags->precision > 0)
	{
		if (flags->precision - e >= 1 && iflt.mts_dec[flags->precision - e - 1])
			break ;
		else if (flags->precision - e < 1 &&
					iflt.int_dec[FLT_INTSIZE + flags->precision - e - 1])
			break ;
		flags->precision--;
	}
	return (ft_printf_putfloat_e(iflt_o, flags));
}

int				ft_printf_putfloat_g(t_float iflt, t_printf_flags *flags)
{
	int				e;
	const t_float	iflt_o = iflt;

	if (flags->precision == 0)
		flags->precision = 1;
	ft_float_round(&iflt, -flags->precision + 1);
	e = ft_printf_putfloat_e_get(iflt, flags);
	iflt = iflt_o;
	if (e < -4 || e >= flags->precision)
		return (ft_putinstyle_e(iflt, flags, e));
	else
		return (ft_putinstyle_f(iflt, flags));
}
