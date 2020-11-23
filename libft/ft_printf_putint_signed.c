/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putint_signed.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:57:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:42:59 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_llong	ft_printf_putsignedint_storenbr(va_list *ap,
					t_printf_flags *flags)
{
	if (flags->flag & FLAG_LONGLONG)
		return (va_arg(*ap, t_llong));
	else if (flags->flag & FLAG_LONG)
		return (va_arg(*ap, long));
	else if (flags->flag & FLAG_SHORTSHORT)
		return ((char)va_arg(*ap, int));
	else if (flags->flag & FLAG_SHORT)
		return ((short)va_arg(*ap, int));
	return (va_arg(*ap, int));
}

int				ft_printf_putsignedint(va_list *ap, t_printf_flags *flags)
{
	t_llong			nbr;
	int				nbrwidth;
	const t_uint	radix = 10;

	nbr = ft_printf_putsignedint_storenbr(ap, flags);
	nbrwidth = ft_printf_putnbr_width_digit(nbr, radix, flags);
	if (flags->precision >= 0)
		flags->flag = flags->flag & ~FLAG_ZEROPADDING;
	if (flags->flag & FLAG_ZEROPADDING)
		ft_printf_putsign(nbr < 0, flags);
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	if (!(flags->flag & FLAG_ZEROPADDING))
		ft_printf_putsign(nbr < 0, flags);
	if (!(nbr == 0 && flags->precision == 0))
		ft_printf_putnbr_base_digit(nbr, radix, flags->precision, 0);
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}
