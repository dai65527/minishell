/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_strdup_skip_bslash.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:34:32 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/21 08:53:46 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	sub_msh_strdup_skip_bslash(char *s, char *substr,
										size_t s_len, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len && j < s_len)
	{
		if (s[j] != '\\' || (s[j] == '\\' && msh_isescaped(s + j, j)))
			substr[i++] = s[j];
		j++;
	}
	substr[len] = 0;
}

char		*msh_strdup_skip_bslash(char *s)
{
	size_t	s_len;
	size_t	len;
	char	*substr;
	char	*head;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	len = s_len;
	head = s;
	while (*s)
	{
		if (*s == '\\' && !msh_isescaped(s, head - s))
			len--;
		s++;
	}
	if (!(substr = (char *)malloc(len + 1)))
		return (NULL);
	sub_msh_strdup_skip_bslash(head, substr, s_len, len);
	return (substr);
}
