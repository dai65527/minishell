/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:15:09 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/12 18:15:35 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

size_t		ft_putstrn_fd(char *s, int fd, size_t n)
{
	size_t	count;

	count = 0;
	while (s[count] && count < n)
		write(fd, s + count++, 1);
	return (count);
}
