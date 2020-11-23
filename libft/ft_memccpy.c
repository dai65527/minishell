/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 06:30:16 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/08 13:14:26 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		i;
	t_uchar		*dst_c;
	t_uchar		*src_c;

	dst_c = (t_uchar *)dst;
	src_c = (t_uchar *)src;
	i = 0;
	while (i < n)
	{
		dst_c[i] = src_c[i];
		if (src_c[i] == (t_uchar)c)
			return (dst_c + i + 1);
		i++;
	}
	return (NULL);
}
