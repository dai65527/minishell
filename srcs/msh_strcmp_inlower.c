/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_strcmp_inlower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:24:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/26 07:42:47 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		tolower_with_ignored_int(unsigned int i, char c)
{
	(void)i;
	return ((char)ft_tolower(c));
}

int				msh_strcmp_inlower(const char *s1, const char *s2)
{
	int		ret;
	char	*s1_inlower;
	char	*s2_inlower;

	if (!(s1_inlower = ft_strmapi(s1, tolower_with_ignored_int)))
		return (-1);
	if (!(s2_inlower = ft_strmapi(s2, tolower_with_ignored_int)))
	{
		free(s1_inlower);
		return (-1);
	}
	ret = ft_strncmp(s1_inlower, s2_inlower, ft_strlen(s2_inlower) + 1);
	free(s1_inlower);
	free(s2_inlower);
	return (ret);
}
