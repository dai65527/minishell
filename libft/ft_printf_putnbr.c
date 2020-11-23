/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 11:02:54 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:42:55 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_putnbr_width_digit(t_llong nbr, t_uint radix,
			t_printf_flags *flags)
{
	int			count;
	int			digit;
	t_ullong	nbr_abs;

	digit = flags->precision;
	count = 0;
	if (nbr < 0 || flags->flag & (FLAG_PUTPOSSPACE | FLAG_PUTPOSSIGN))
		count++;
	if (nbr == 0)
	{
		if (digit == 0)
			return (flags->flag & (FLAG_PUTPOSSPACE | FLAG_PUTPOSSIGN) ? 1 : 0);
		return (digit > 1 ? digit + count : 1 + count);
	}
	nbr_abs = nbr < 0 ? -nbr : nbr;
	while (nbr_abs > 0 || digit > 0)
	{
		nbr_abs /= radix;
		digit--;
		count++;
	}
	return (count);
}

int		ft_printf_putnbr_unsigned_width_digit(t_ullong nbr, t_uint radix,
			t_printf_flags *flags)
{
	int			count;
	int			digit;

	digit = flags->precision;
	count = 0;
	if (nbr == 0)
	{
		if (digit == 0)
			return (0);
		return (digit > 1 ? digit + count : 1 + count);
	}
	while (nbr > 0 || digit > 0)
	{
		nbr /= radix;
		digit--;
		count++;
	}
	return (count);
}

void	ft_printf_putnbr_unsigned_base_digit(t_ullong nbr, t_uint radix,
			int digit, int flag_upcase)
{
	const char	*base;
	const char	baselow[] = "0123456789abcdef";
	const char	baseup[] = "0123456789ABCDEF";

	if (radix > 16)
		return ;
	base = (flag_upcase ? baseup : baselow);
	if (nbr >= radix || digit - 1 > 0)
		ft_printf_putnbr_unsigned_base_digit(nbr / radix, radix, digit - 1,
												flag_upcase);
	ft_putchar_fd(base[nbr % radix], 1);
}

void	ft_printf_putnbr_base_digit(t_llong nbr, t_uint radix, int digit,
			int flag_upcase)
{
	t_ullong	nbr_abs;

	nbr_abs = nbr < 0 ? -nbr : nbr;
	ft_printf_putnbr_unsigned_base_digit(nbr_abs, radix, digit, flag_upcase);
}
