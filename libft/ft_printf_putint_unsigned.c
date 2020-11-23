/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putint_unsigned.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:57:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:42:57 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_ullong	ft_printf_putunsignedint_storenbr(va_list *ap,
					t_printf_flags *flags)
{
	if (flags->flag & FLAG_LONGLONG)
		return ((t_ullong)va_arg(*ap, t_llong));
	else if (flags->flag & FLAG_LONG)
		return ((t_ulong)va_arg(*ap, long));
	else if (flags->flag & FLAG_SHORTSHORT)
		return ((t_uchar)va_arg(*ap, int));
	else if (flags->flag & FLAG_SHORT)
		return ((t_ushort)va_arg(*ap, int));
	return (va_arg(*ap, t_uint));
}

static int		ft_getradix(const char fc)
{
	if (fc == 'u')
		return (10);
	else if (fc == 'o')
		return (8);
	return (16);
}

int				ft_printf_putunsignedint(va_list *ap, t_printf_flags *flags,
					const char fc)
{
	t_ullong	nbr;
	int			nbrwidth;
	t_uint		radix;

	radix = ft_getradix(fc);
	nbr = ft_printf_putunsignedint_storenbr(ap, flags);
	nbrwidth = ft_printf_putnbr_unsigned_width_digit(nbr, radix, flags);
	if ((flags->flag & FLAG_ALTERNATE) &&
			(fc == 'x' || fc == 'X' || fc == 'o') && nbr)
		nbrwidth += (fc == 'o') ? 1 : 2;
	if (flags->precision >= 0)
		flags->flag = flags->flag & ~FLAG_ZEROPADDING;
	if ((flags->flag & FLAG_ALTERNATE) && (flags->flag & FLAG_ZEROPADDING))
		ft_printf_putintalternate(nbr ? fc : 0);
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	if ((flags->flag & FLAG_ALTERNATE) && !(flags->flag & FLAG_ZEROPADDING))
		ft_printf_putintalternate(nbr ? fc : 0);
	if (!(nbr == 0 && flags->precision == 0))
		ft_printf_putnbr_unsigned_base_digit(nbr, radix, flags->precision,
												ft_isupper(fc));
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}
