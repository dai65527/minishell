/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:45:09 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/30 13:34:27 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** init prams for msh_get_argv
*/

static void		init_params(char *content[2], ssize_t begin[2], ssize_t len)
{
	content[0] = NULL;
	content[1] = NULL;
	begin[0] = len;
}

/*
** store plain argv into content[0]
*/

static ssize_t	store_plain_argv(char *save, ssize_t begin[2],
								char *content[2], ssize_t *len)
{
	while (msh_check_operator(save, *len, "$><| \t\'\"\n;"))
		(*len)++;
	if (begin[1] == *len && !ft_strchr("$\'\"", save[*len]))
		return (0);
	if (begin[1] != *len
		&& !(content[1] = ft_substr(save, begin[1], *len - begin[1])))
		return (-1);
	return (0);
}

/*
** call funcs handling env and quote
*/

static ssize_t	handle_env_quote(t_mshinfo *mshinfo, char *save, ssize_t len,
								char **content)
{
	ssize_t	ret;
	ssize_t begin;

	ret = 0;
	begin = len;
	if (save[len] == '$'
		&& ((ret = msh_get_env(mshinfo, save, len, content)) < 0))
		return (-1);
	len += ret;
	if ((ret = msh_handle_quote(mshinfo, save, len, content)) < 0)
		return (-1);
	len += ret;
	return (len - begin);
}

/*
** store content into arglst
*/

static ssize_t	store_arglst(t_mshinfo *mshinfo, char **content)
{
	if (*content)
	{
		if (msh_content_arglst(mshinfo, ft_strdup(*content)))
			return (-1);
		msh_free_setnull((void**)content);
	}
	return (0);
}

/*
** get plain argv and call funcs hadling env and quotes
*/

ssize_t			msh_get_argv(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	ssize_t	begin[2];
	ssize_t	ret;
	char	*content[2];

	init_params(content, begin, len);
	while (msh_check_operator(save, len, "><| \t\n;"))
	{
		ret = 0;
		begin[1] = len;
		if (store_plain_argv(save, begin, content, &len))
			return (msh_puterr(MSH_NAME, "malloc", -1));
		if (msh_store_val_content(&content[1], &content[0], 0))
			return (msh_puterr(MSH_NAME, "malloc", -1));
		if ((ret = handle_env_quote(mshinfo, save, len, &content[0])) < 0)
			return (-1);
		len += ret;
	}
	if (store_arglst(mshinfo, &content[0]))
		return (msh_puterr(MSH_NAME, "malloc", -1));
	return (len - begin[0]);
}
