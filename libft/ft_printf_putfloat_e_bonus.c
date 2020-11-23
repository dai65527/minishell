/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putfloat_e_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:36:42 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:43:09 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf_putfloat_e_get(t_float iflt, t_printf_flags *flags)
{
	int			e;

	if (iflt.exp == -FLT_EXPBIAS && !iflt.frac)
		return (0);
	e = FLT_INTSIZE;
	while (--e > -FLT_MTSSIZE)
	{
		if (e >= 0 && iflt.int_dec[FLT_INTSIZE - (e + 1)])
		{
			ft_float_round(&iflt, e - flags->precision);
			if (e != FLT_INTSIZE - 1 && iflt.int_dec[FLT_INTSIZE - (e + 2)])
				return (e + 1);
			return (e);
		}
		if (e < 0 && iflt.mts_dec[-(e + 1)])
		{
			ft_float_round(&iflt, e - flags->precision);
			if (e == -1 && iflt.int_dec[0])
				return (0);
			else if (iflt.mts_dec[-(e + 2)])
				return (e + 1);
			return (e);
		}
	}
	return (0);
}

static int		ft_printf_putfloat_e_width(t_float iflt, t_printf_flags *flags,
											int e)
{
	int		width;

	if (iflt.exp == (FLT_EXPBIAS + 1))
	{
		if (iflt.sign || flags->flag & (FLAG_PUTPOSSPACE | FLAG_PUTPOSSIGN))
			return (4);
		return (3);
	}
	width = (-100 < e && e < 100) ? 4 : 5;
	width += (flags->precision || flags->flag & FLAG_ALTERNATE)
				? flags->precision + 1 : 0;
	if (iflt.sign || flags->flag & (FLAG_PUTPOSSPACE | FLAG_PUTPOSSIGN))
		return (width + 2);
	return (width + 1);
}

static void		ft_printf_putfloat_e_pute(int e)
{
	ft_putchar_fd('e', 1);
	if (e >= 0)
		ft_putchar_fd('+', 1);
	else
	{
		ft_putchar_fd('-', 1);
		e = -e;
	}
	if (e < 10)
		ft_putchar_fd('0', 1);
	ft_putnbr_fd(e, 1);
}

static void		ft_printf_putfloat_e_put(t_float iflt, t_printf_flags *flags,
											int e)
{
	int		i;

	if (iflt.exp == (FLT_EXPBIAS + 1))
	{
		ft_putnaninf(!!iflt.frac);
		return ;
	}
	if (e >= 0)
		ft_putchar_fd(iflt.int_dec[FLT_INTSIZE - e - 1] + '0', 1);
	else
		ft_putchar_fd(iflt.mts_dec[-(e + 1)] + '0', 1);
	if (flags->precision || flags->flag & FLAG_ALTERNATE)
		ft_putchar_fd('.', 1);
	i = 1;
	while (i <= flags->precision)
	{
		if (i - e <= 0)
			ft_putchar_fd(iflt.int_dec[FLT_INTSIZE - (e - i) - 1] + '0', 1);
		else if (i - e < FLT_MTSSIZE - 1)
			ft_putchar_fd(iflt.mts_dec[-(e - i) - 1] + '0', 1);
		else
			ft_putchar_fd('0', 1);
		i++;
	}
	ft_printf_putfloat_e_pute(e);
}

int				ft_printf_putfloat_e(t_float iflt, t_printf_flags *flags)
{
	int			nbrwidth;
	int			e;

	flags->flag &= ~(FLAG_ZEROPADDING);
	e = ft_printf_putfloat_e_get(iflt, flags);
	ft_float_round(&iflt, e - flags->precision);
	nbrwidth = ft_printf_putfloat_e_width(iflt, flags, e);
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	ft_printf_putsign(iflt.sign, flags);
	ft_printf_putfloat_e_put(iflt, flags, e);
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}
