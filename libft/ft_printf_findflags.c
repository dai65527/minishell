/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_findflags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:49:46 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:42:18 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_printf_setwidth(const char *format, t_printf_flags *flags)
{
	t_uint	res;

	if (*format == '0' && flags->precision != -2)
	{
		flags->flag = flags->flag | FLAG_ZEROPADDING;
		format++;
	}
	res = 0;
	while (ft_isdigit(*format))
	{
		res = res * 10 + *(format++) - '0';
	}
	if (flags->precision == -2)
		flags->precision = res;
	else
		flags->width = res;
	return ((char *)format);
}

static int		ft_printf_isflag(int c)
{
	int			i;
	const char	flag_char[] = "-.*lh# +";

	if (ft_isdigit(c))
		return (1);
	i = 0;
	while (flag_char[i])
	{
		if (c == flag_char[i])
			return (1);
		i++;
	}
	return (0);
}

static void		ft_printf_findflags_lh(char fc, t_printf_flags *flags)
{
	if (fc == 'l')
	{
		if (flags->flag & FLAG_LONG)
			flags->flag = flags->flag | FLAG_LONGLONG;
		else
			flags->flag = flags->flag | FLAG_LONG;
	}
	else if (fc == 'h')
	{
		if (flags->flag & FLAG_SHORT)
			flags->flag = flags->flag | FLAG_SHORTSHORT;
		else
			flags->flag = flags->flag | FLAG_SHORT;
	}
}

static void		ft_printf_findflags_getarg(va_list *ap, t_printf_flags *flags)
{
	if (flags->precision == -2)
	{
		flags->precision = va_arg(*ap, long);
		if (flags->precision == -2)
			flags->precision = -1;
	}
	else
		ft_printf_getwidth(va_arg(*ap, long), flags);
}

char			*ft_printf_findflags(const char *format, va_list *ap,
										t_printf_flags *flags)
{
	ft_printf_initflags(flags);
	while (*format && ft_printf_isflag(*format))
	{
		if (*format == '-')
			flags->flag = flags->flag | FLAG_LEFTADJUST;
		if (*format == '+')
			flags->flag = flags->flag | FLAG_PUTPOSSIGN;
		if (*format == ' ')
			flags->flag = flags->flag | FLAG_PUTPOSSPACE;
		if (*format == '#')
			flags->flag = flags->flag | FLAG_ALTERNATE;
		if (*format == '*')
			ft_printf_findflags_getarg(ap, flags);
		if (*format == '.')
			flags->precision = -2;
		if (*format == 'l' || *format == 'h')
			ft_printf_findflags_lh(*format, flags);
		if (ft_isdigit(*format))
			format = ft_printf_setwidth(format, flags);
		else
			format++;
	}
	if (flags->precision == -2)
		flags->precision = 0;
	return ((char *)format);
}
