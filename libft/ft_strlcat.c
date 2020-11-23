/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:45:05 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/08 13:18:25 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	if (dst[i] == '\0' && i != dstsize)
		return (ft_strlcpy(dst + i, src, dstsize - i) + i);
	return (i + ft_strlen(src));
}
