/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 11:53:55 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/06 19:42:06 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*pt;

	pt = NULL;
	i = 0;
	while (s[i] || !c)
	{
		if (s[i] == (char)c)
		{
			pt = (char *)(s + i);
			if (!c)
				break ;
		}
		i++;
	}
	return (pt);
}
