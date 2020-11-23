/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putint_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:57:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:43:01 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf_putint(const char fc, va_list *ap,
									t_printf_flags *flags)
{
	int		count;

	count = 0;
	if (fc == 'd' || fc == 'i')
		count = ft_printf_putsignedint(ap, flags);
	else if (fc == 'u' || fc == 'x' || fc == 'X' || fc == 'o')
		count = ft_printf_putunsignedint(ap, flags, fc);
	return (count);
}
