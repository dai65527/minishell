/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:56:20 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/28 19:25:53 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** get env in quatation
*/

static ssize_t	get_env_quote(t_mshinfo *mshinfo, char *save,
									ssize_t len, char **content)
{
	ssize_t	begin;
	ssize_t ret;
	char	*key;
	char	*val;

	if ((ret = msh_handle_dollars(save, len, &content, 1)))
		return (ret);
	begin = ++len;
	if ((ret = msh_handle_special_var(mshinfo, save, &content, len)) < 0)
		return (-1);
	if (ret)
		return (ret);
	while (msh_check_operator(save, len, "$<>|\'\" \t"))
		len++;
	if (!(key = ft_substr(save, begin, len - begin)))
		return (-1);
	val = msh_get_value_from_envlst(mshinfo, &key, 1);
	msh_free_set(content, ft_strjoin(*content, val));
	msh_free_setnull((void**)&val);
	if (!*content)
		return (-1);
	return (len - (begin - 1));
}

/*
** function handling "" case
*/

static ssize_t	handle_empty_quote(ssize_t len, ssize_t begin, char **content)
{
	char	*val;

	val = NULL;
	if (!(len - begin))
	{
		if (!(val = ft_strdup("")))
			return (-1);
		if (msh_store_val_content(&val, content))
			return (-1);
	}
	return (0);
}

/*
** get argv in double quotation
*/

static ssize_t	get_argv_quote(t_mshinfo *mshinfo, char *save, ssize_t len,
								char **content)
{
	ssize_t	begin[2];
	ssize_t	ret;
	char	*val;

	val = NULL;
	begin[0] = len;
	while (msh_check_operator(save, len, "\""))
	{
		ret = 0;
		begin[1] = len;
		while (msh_check_operator(save, len, "$\""))
			len++;
		if (!(val = ft_substr(save, begin[1], len - begin[1])))
			return (-1);
		if (msh_store_val_content(&val, content))
			return (-1);
		if (save[len] == '$' && ((ret = get_env_quote(mshinfo,
			save, len, &content[0])) < 0))
			return (-1);
		len += ret;
	}
	if (handle_empty_quote(len, begin[0], content))
		return (-1);
	return (len - begin[0]);
}

/*
** handle single and double quatation
** for single, store argv to arglst here
** for double call func to store argv
*/

ssize_t			msh_handle_quote(t_mshinfo *mshinfo, char *save, ssize_t len,
								char **content)
{
	ssize_t ret;
	ssize_t	begin;
	char	*val;

	val = NULL;
	if (!ft_strchr("\'\"", save[len]))
		return (0);
	if (save[len] == '\'')
	{
		begin = ++len;
		while (msh_check_operator(save, len, "\'"))
			len++;
		if (!(val = ft_substr(save, begin, len++ - begin)))
			return (-1);
		if (msh_store_val_content(&val, content))
			return (-1);
		return (len - (begin - 1));
	}
	ret = 0;
	begin = ++len;
	if ((ret = get_argv_quote(mshinfo, save, len, content)) < 0)
		return (msh_puterr(MSH_NAME, "malloc", -1));
	len += ret;
	return (++len - (begin - 1));
}
