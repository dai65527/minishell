/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_store_n_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 10:25:16 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 12:42:45 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_store_n(va_list *ap, t_printf_flags *flags, int count)
{
	long long		*n;

	n = (long long *)va_arg(*ap, t_ullong);
	if (flags->flag & FLAG_LONGLONG)
		*n = (long long)count;
	else if (flags->flag & FLAG_LONG)
		*n = (long)count;
	else if (flags->flag & FLAG_SHORTSHORT)
		*n = (signed char)count;
	else if (flags->flag & FLAG_SHORT)
		*n = (short)count;
	else
		*n = (int)count;
}
