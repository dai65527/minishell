/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putfloat_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:36:42 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:43:11 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf_putfloat(const char fc, va_list *ap,
									t_printf_flags *flags)
{
	int			count;
	double		nbr;
	t_float		iflt;

	nbr = va_arg(*ap, double);
	iflt = ft_store_iflt(nbr);
	if (iflt.exp == (FLT_EXPBIAS + 1) && !!iflt.frac)
		flags->flag &= ~(FLAG_PUTPOSSIGN | FLAG_PUTPOSSPACE);
	if (flags->precision < 0)
		flags->precision = 6;
	count = 0;
	if (fc == 'f')
		count = ft_printf_putfloat_f(iflt, flags);
	else if (fc == 'e')
		count = ft_printf_putfloat_e(iflt, flags);
	else if (fc == 'g')
		count = ft_printf_putfloat_g(iflt, flags);
	return (count);
}
