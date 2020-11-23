/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 08:31:16 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/07 22:55:43 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst_c;
	char	*src_c;

	if (!dst && !src)
		return (NULL);
	if (dst <= src)
		return (ft_memcpy(dst, src, len));
	dst_c = (char *)dst;
	src_c = (char *)src;
	i = len;
	while (i > 0)
	{
		dst_c[i - 1] = src_c[i - 1];
		i--;
	}
	return (dst);
}
