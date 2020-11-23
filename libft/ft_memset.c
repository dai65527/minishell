/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 20:16:03 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/06 19:41:19 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	size_t		i;
	t_uchar		*b_uchar;

	b_uchar = (void *)b;
	i = 0;
	while (i < len)
		b_uchar[i++] = c;
	return (b);
}
