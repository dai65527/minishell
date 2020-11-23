/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putbyte.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 11:52:05 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:43:13 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_putbyte(va_list *ap, t_printf_flags *flags)
{
	t_uchar	c;

	if (flags->width == -1)
		flags->width = 0;
	c = (t_uchar)va_arg(*ap, t_ullong);
	if (flags->flag & FLAG_LEFTADJUST)
		ft_putchar_fd(c, 1);
	ft_printf_putpadding(flags->width - 1, flags);
	if (!(flags->flag & FLAG_LEFTADJUST))
		ft_putchar_fd(c, 1);
	return (flags->width ? flags->width : 1);
}
