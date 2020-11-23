/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:37:43 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/08 11:53:22 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needlelen;

	needlelen = ft_strlen(needle);
	i = 0;
	while (i + needlelen <= len)
	{
		if (!ft_strncmp(haystack + i, needle, needlelen))
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
