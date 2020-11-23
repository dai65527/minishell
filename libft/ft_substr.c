/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 19:57:27 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/12 18:12:16 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_substr(char const *s, t_uint start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	s_len = ft_strlen(s);
	if (s_len < start)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[len] = 0;
	return (substr);
}
