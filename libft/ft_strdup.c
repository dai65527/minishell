/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:44:47 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/12 18:12:27 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(s1);
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, len + 1);
	return (dest);
}
