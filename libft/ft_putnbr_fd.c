/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:00:03 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/11 07:57:11 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		putabs_fd(t_uint n, int fd)
{
	if (n < 10)
		ft_putchar_fd(n + '0', fd);
	else
	{
		putabs_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

void			ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		putabs_fd(-(long)n, fd);
	}
	else
		putabs_fd(n, fd);
}
