/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:56:20 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/26 18:28:56 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	handle_special_var(t_mshinfo *mshinfo, char *save,
									char ***content, ssize_t *len)
{
	char	*val;

	if (save[*len] != '?')
		return (0);
	val = ft_itoa(mshinfo->ret_last_cmd);
	if (!val)
		return (-1);
	if (!**content)
		**content = ft_strdup(val);
	else
		msh_free_set(*content, ft_strjoin(**content, val));
	msh_free_setnull((void**)&val);
	if (!**content)
		return (-1);
	++(*len);
	return (1);
}

/*
** get env in quatation
*/

static ssize_t	get_env_quate(t_mshinfo *mshinfo, char *save,
									ssize_t len, char **content)
{
	ssize_t	begin;
	ssize_t ret;
	char	*key;

	if ((ret = msh_handle_dollars(mshinfo, save, len)))
		return (ret);
	begin = ++len;
	if ((ret = handle_special_var(mshinfo, save, &content, &len)) < 0)
		return (-1);
	if (ret)
		return (len - (begin - 1));
	while (msh_check_operator(save, len, "$<>|\'\""))
		len++;
	if (!(key = ft_substr(save, begin, len - begin)))
		return (-1);
	msh_free_set(content,
		ft_strjoin(*content, msh_get_value_from_envlst(mshinfo, &key, 1)));
	if (!*content)
		return (-1);
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
