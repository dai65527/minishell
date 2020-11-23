/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putpadding.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 09:02:48 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:42:53 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf_putpadding(int width, t_printf_flags *flags)
{
	while (width > 0)
	{
		if (flags->flag & FLAG_ZEROPADDING && !(flags->flag & FLAG_LEFTADJUST))
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(' ', 1);
		width--;
	}
}
