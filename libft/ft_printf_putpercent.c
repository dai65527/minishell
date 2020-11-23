/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putpercent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:59:45 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:42:51 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf_putpercent(t_printf_flags *flags)
{
	if (flags->width == -1)
		flags->width = 0;
	if (flags->flag & FLAG_LEFTADJUST)
		ft_putchar_fd('%', 1);
	ft_printf_putpadding(flags->width - 1, flags);
	if (!(flags->flag & FLAG_LEFTADJUST))
		ft_putchar_fd('%', 1);
	return (flags->width ? flags->width : 1);
}
