/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putfloat_f_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:36:42 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:43:07 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_printf_putfloat_f_width(t_float iflt, t_printf_flags *flags)
{
	int		intwidth;
	int		mstwidth;

	if (iflt.exp == (FLT_EXPBIAS + 1))
	{
		if (iflt.sign || flags->flag & (FLAG_PUTPOSSPACE | FLAG_PUTPOSSIGN))
			return (4);
		return (3);
	}
	ft_float_round(&iflt, -flags->precision);
	mstwidth = (flags->precision || flags->flag & FLAG_ALTERNATE)
				? flags->precision + 1 : 0;
	intwidth = FLT_INTSIZE;
	while (intwidth > 1 && !iflt.int_dec[FLT_INTSIZE - intwidth])
		intwidth--;
	if (iflt.sign || flags->flag & (FLAG_PUTPOSSPACE | FLAG_PUTPOSSIGN))
		return (intwidth + mstwidth + 1);
	return (intwidth + mstwidth);
}

static void		ft_printf_putfloat_f_put(t_float iflt, t_printf_flags *flags)
{
	int		i;

	if (iflt.exp == (FLT_EXPBIAS + 1))
	{
		ft_putnaninf(!!iflt.frac);
		return ;
	}
	ft_float_round(&iflt, -flags->precision);
	i = 0;
	while (!iflt.int_dec[i] && i < FLT_INTSIZE - 1)
		i++;
	while (i < FLT_INTSIZE)
		ft_putchar_fd(iflt.int_dec[i++] + '0', 1);
	if (flags->precision || flags->flag & FLAG_ALTERNATE)
		ft_putchar_fd('.', 1);
	i = 0;
	while (i < flags->precision)
	{
		if (i < FLT_MTSSIZE - 1)
			ft_putchar_fd(iflt.mts_dec[i] + '0', 1);
		else
			ft_putchar_fd('0', 1);
		i++;
	}
}

int				ft_printf_putfloat_f(t_float iflt, t_printf_flags *flags)
{
	int			nbrwidth;

	if (iflt.exp == (FLT_EXPBIAS + 1))
		flags->flag &= ~(FLAG_ZEROPADDING);
	nbrwidth = ft_printf_putfloat_f_width(iflt, flags);
	if (flags->flag & FLAG_ZEROPADDING)
		ft_printf_putsign(iflt.sign, flags);
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	if (!(flags->flag & FLAG_ZEROPADDING))
		ft_printf_putsign(iflt.sign, flags);
	ft_printf_putfloat_f_put(iflt, flags);
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}
