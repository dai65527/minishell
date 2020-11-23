/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 05:41:52 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/08 13:17:53 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_c;
	char	*src_c;

	if (!dst && !src)
		return (NULL);
	dst_c = (char *)dst;
	src_c = (char *)src;
	i = 0;
	while (i < n)
	{
		dst_c[i] = src_c[i];
		i++;
	}
	return (dst);
}
