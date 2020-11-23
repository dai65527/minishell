/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 10:52:10 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/12 18:12:28 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		*find_str(char const *s, char c, char opt)
{
	while (opt == 'n' && *s == c && *s)
		s++;
	while (opt == 'e' && *s != c && *s)
		s++;
	return ((char *)s);
}

static size_t	num_of_strs(char const *s, char c)
{
	size_t		count;

	count = 0;
	while (*s)
	{
		s = find_str(s, c, 'n');
		if (*s)
			count++;
		s = find_str(s, c, 'e');
	}
	return (count);
}

static size_t	split_strlen(char const *s, char c)
{
	size_t		count;

	count = 0;
	while (s[count] != c && s[count])
		count++;
	return (count);
}

static void		*free_strs(char **strs, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	size_t		i;
	char		**strs;
	size_t		n_strs;
	size_t		len;

	n_strs = num_of_strs(s, c);
	strs = (char **)malloc(sizeof(char *) * (n_strs + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < n_strs)
	{
		s = find_str(s, c, 'n');
		len = split_strlen(s, c);
		strs[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!strs[i])
			return (free_strs(strs, i));
		ft_strlcpy(strs[i], s, len + 1);
		s = find_str(s, c, 'e');
		i++;
	}
	strs[n_strs] = NULL;
	return (strs);
}
