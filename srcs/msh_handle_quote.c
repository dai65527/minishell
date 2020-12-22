/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:56:20 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/20 22:10:15 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** get env in quatation
*/

static ssize_t	get_env_quate(t_mshinfo *mshinfo, char *save,
									ssize_t len, char **content)
{
	ssize_t	begin;
	char	*key;

	if (msh_handle_dollars(mshinfo, save, len))
		return (2);
	begin = ++len;
	while (msh_check_operator(save, len, "$<>|\'\""))
		len++;
	if (!(key = ft_substr(save, begin, len - begin)))
		ft_putendl_fd("msh_put_errmsg", 2);
	msh_free_set(content,
		ft_strjoin(*content, msh_get_value_from_envlst(mshinfo, &key)));
	if (!*content)
		ft_putendl_fd("msh_put_errmsg", 2);
	return (len - (begin - 1));
}

/*
** get argv in double quotation
*/

static ssize_t	get_argv_quote(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	ssize_t	ret;
	ssize_t	begin[2];
	char	*content[2];

	if (!(content[0] = ft_strdup("")))
		return (-1);
	begin[0] = len;
	while (msh_check_operator(save, len, "\""))
	{
		ret = 0;
		begin[1] = len;
		while (msh_check_operator(save, len, "$\""))
			len++;
		if (!(content[1] = ft_substr(save, begin[1], len - begin[1])))
			return (-1);
		msh_free_set(&content[0], ft_strjoin(content[0], content[1]));
		msh_free_setnull((void**)&content[1]);
		if (save[len] == '$'
			&& ((ret = get_env_quate(mshinfo, save, len, &content[0])) < 0))
			return (-1);
		len += ret;
	}
	if (msh_content_arglst(mshinfo, content[0]))
		return (-1);
	return (len - begin[0]);
}

/*
** handle single and double quatation
** for single, store argv to arglst here
** for double call func to store argv
*/

ssize_t			msh_handle_quote(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	ssize_t ret;
	ssize_t	begin;

	if (!ft_strchr("\'\"", save[len]))
		return (0);
	if (save[len] == '\'')
	{
		begin = ++len;
		while (msh_check_operator(save, len, "\'"))
			len++;
		if (save[len] != '\'')
			return (msh_msg_return_val("syntax error", 2, -1));
		if (msh_content_arglst(mshinfo, ft_substr(save, begin, len++ - begin)))
			return (msh_msg_return_val("malloc error", 2, -1));
		return (len - (begin - 1));
	}
	ret = 0;
	begin = ++len;
	if ((ret = get_argv_quote(mshinfo, save, len)) < 0)
		return (msh_msg_return_val("malloc error", 2, -1));
	len += ret;
	if (save[len++] != '\"')
		return (msh_msg_return_val("syntax error", 2, -1));
	return (len - (begin - 1));
}
