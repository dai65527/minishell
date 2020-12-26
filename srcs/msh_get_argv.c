/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:45:09 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/26 17:27:12 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		store_content(char ***content, char **val)
{
	if (!**content)
		**content = ft_strdup(*val);
	else
		msh_free_set(*content, ft_strjoin(**content, *val));
	msh_free_setnull((void**)val);
	if (!**content)
		return (-1);
	return (0);
}

static ssize_t	handle_special_var(t_mshinfo *mshinfo, char *save,
									char ***content, ssize_t *len)
{
	char	*val;
	ssize_t	begin;

	if (save[*len] != '?')
		return (0);
	val = ft_itoa(mshinfo->ret_last_cmd);
	if (!val)
		return (-1);
	if (store_content(content, &val))
		return (-1);
	begin = ++(*len);
	while (msh_check_operator(save, *len, "$><| \t\'\"\n;"))
		(*len)++;
	if (begin == *len && save[*len] != '$')
		return (1);
	if (begin != *len)
	{
		msh_free_set(&val, ft_substr(save, begin, *len - begin));
		if (store_content(content, &val))
			return (-1);
	}
	return (1);
}

static ssize_t	msh_get_env(t_mshinfo *mshinfo, char *save,
							ssize_t len, char **content)
{
	ssize_t	begin;
	ssize_t	ret;
	char	*key;
	char	*val;

	if ((ret = msh_handle_dollars(mshinfo, save, len)) != 0)
		return (ret);
	while (msh_check_operator(save, len, "><| \t\'\"\n;"))
	{
		begin = ++len;
		if ((ret = handle_special_var(mshinfo, save, &content, &len)) < 0)
			return (-1);
		if (ret)
			continue ;
		while (msh_check_operator(save, len, "$><| \t\'\"\n;"))
			len++;
		if (!(key = ft_substr(save, begin, len - begin)))
			return (-1);
		if (!(val = msh_get_value_from_envlst(mshinfo, &key, 0)))
			return (len - (begin - 1));
		if (store_content(&content, &val))
			return (-1);
	}
	return (len - (begin - 1));
}

/*
** get argv and handle '$'
*/

ssize_t			msh_get_argv(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	ssize_t	begin;
	ssize_t	ret;
	char	*content;

	content = NULL;
	begin = len;
	ret = 0;
	while (msh_check_operator(save, len, "$><| \t\'\"\n;"))
		len++;
	if (begin == len && save[len] != '$')
		return (0);
	if (begin != len && !(content = ft_substr(save, begin, len - begin)))
		return (msh_msg_return_val("malloc error", 2, -1));
	if (save[len] == '$'
		&& ((ret = msh_get_env(mshinfo, save, len, &content)) < 0))
		return (msh_msg_return_val("malloc error", 2, -1));
	len += ret;
	if (content)
	{
		msh_free_set(&content, msh_strdup_skip_bslash(content));
		if (msh_content_arglst(mshinfo, content))
			return (msh_msg_return_val("malloc error", 2, -1));
	}
	return (len - begin);
}
