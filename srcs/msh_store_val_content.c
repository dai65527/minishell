/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_store_val_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:52:36 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/30 12:26:22 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
** copy substring with calculated number of backslash
*/

static void		copy_handling_bslash(char *s, char *substr,
										size_t s_len, size_t len)
{
	size_t	sub_index;
	size_t	s_index;
	size_t	cnt;

	sub_index = 0;
	s_index = 0;
	while (sub_index < len && s_index < s_len)
	{
		cnt = 0;
		while (s[s_index] && s[s_index] == '\\')
		{
			cnt++;
			if (cnt % 2)
				substr[sub_index++] = s[s_index];
			s_index++;
		}
		if ((s[s_index] == '$' || s[s_index] == '"') && cnt % 2)
			sub_index--;
		substr[sub_index++] = s[s_index];
		s_index++;
	}
	substr[len] = 0;
}

/*
** set prams for stdup_dquote
*/

static void		init_params(char *s, int *i, int *s_len, size_t *len)
{
	*i = -1;
	*len = 0;
	*s_len = (int)ft_strlen(s);
}

/*
** dedicted func for double quote to handle backslash
*/

static char		*strdup_dquote(char *s)
{
	int		s_len;
	size_t	cnt;
	size_t	len;
	int		i;
	char	*substr;

	init_params(s, &i, &s_len, &len);
	while (++i < s_len)
	{
		cnt = 0;
		while (s[i] && s[i] == '\\')
		{
			cnt++;
			if (cnt % 2)
				len++;
			i++;
		}
		if ((s[i] == '$' || s[i] == '"') && cnt % 2)
			len--;
		len++;
	}
	if (!(substr = (char *)malloc(len + 1)))
		return (NULL);
	copy_handling_bslash(s, substr, s_len, len);
	return (substr);
}

/*
** func store val into content
** if flg_quote == 0, skip back slash
** else if flg_quote == 1, do NOT skip back slash
** ekse if flg_quote == 2, dedicated skip back slash method for double quote
*/

ssize_t			msh_store_val_content(char **val, char **content, int flg_quote)
{
	if (!flg_quote && *val)
	{
		msh_free_set(val, msh_strdup_skip_bslash(*val));
		if (!*val)
			return (-1);
	}
	else if (flg_quote == 2 && *val)
	{
		msh_free_set(val, strdup_dquote(*val));
		if (!*val)
			return (-1);
	}
	if (*content && *val)
		msh_free_set(content, ft_strjoin(*content, *val));
	else if (*val)
		*content = ft_strdup(*val);
	else
		return (0);
	if (!*content)
		return (-1);
	msh_free_setnull((void**)val);
	return (0);
}
