/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:28:17 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:42:41 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_getwidth(int width_arg, t_printf_flags *flags)
{
	if (width_arg < 0)
	{
		flags->width = -width_arg;
		flags->flag = flags->flag | FLAG_LEFTADJUST;
	}
	else
		flags->width = width_arg;
}

void		ft_printf_initflags(t_printf_flags *flags)
{
	flags->width = -1;
	flags->precision = -1;
	flags->flag = 0;
}

void		ft_printf_putsign(int flag_neg, t_printf_flags *flags)
{
	if (flag_neg)
		ft_putchar_fd('-', 1);
	else if (flags->flag & FLAG_PUTPOSSIGN)
		ft_putchar_fd('+', 1);
	else if (flags->flag & FLAG_PUTPOSSPACE)
		ft_putchar_fd(' ', 1);
}

void		ft_printf_putintalternate(const char fc)
{
	if (fc == 'x' || fc == 'p')
		ft_putstr_fd("0x", 1);
	else if (fc == 'X')
		ft_putstr_fd("0X", 1);
	else if (fc == 'o')
		ft_putchar_fd('0', 1);
}
