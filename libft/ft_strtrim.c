/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 06:19:10 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/12 18:12:22 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		isinset(char const c, char const *set)
{
	while (*set)
	{
		if (*(set++) == c)
			return (1);
	}
	return (0);
}

static size_t	trimlen(char const *s1, char const *set)
{
	size_t	count;

	count = 0;
	while (isinset(*s1, set))
		s1++;
	while (*s1)
	{
		s1++;
		count++;
	}
	if (count)
	{
		while (isinset(*(--s1), set))
			count--;
	}
	return (count);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	len;

	len = trimlen(s1, set);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (isinset(*s1, set))
		s1++;
	ft_strlcpy(dst, s1, len + 1);
	return (dst);
}
