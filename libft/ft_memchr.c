/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 10:40:56 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/06 19:40:07 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	t_uchar	*str_uchar;

	str_uchar = (t_uchar *)s;
	while (n > 0)
	{
		if (*str_uchar == (t_uchar)c)
			return (str_uchar);
		str_uchar++;
		n--;
	}
	return (NULL);
}
