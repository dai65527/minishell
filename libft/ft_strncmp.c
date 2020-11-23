/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 09:25:43 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/07 06:42:44 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && ((t_uchar)(*s1) != '\0' || (t_uchar)(*s2) != '\0'))
	{
		if ((t_uchar)(*s1) != (t_uchar)(*s2))
			return ((t_uchar)(*s1) - (t_uchar)(*s2));
		s1++;
		s2++;
		n--;
	}
	return (0);
}
