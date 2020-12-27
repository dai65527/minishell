/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:45:09 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/27 12:34:42 by dhasegaw         ###   ########.fr       */
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

static ssize_t	msh_get_env(t_mshinfo *mshinfo, char *save,
							ssize_t len, char **content)
{
	ssize_t	begin;
	ssize_t	ret;
	char	*key;
	char	*val;

	if ((ret = msh_handle_dollars(save, len, &content)) != 0)
		return (ret);
	begin = ++len;
	if ((ret = msh_handle_special_var(mshinfo, save, &content, len)) < 0)
		return (-1);
	if (ret)
		return (ret) ;
	while (msh_check_operator(save, len, "$><| \t\'\"\n;"))
		len++;
	if (!(key = ft_substr(save, begin, len - begin)))
		return (-1);
	if (!(val = msh_get_value_from_envlst(mshinfo, &key, 0)))
		return (len - (begin - 1));
	if (store_content(&content, &val))
		return (-1);
	return (len - (begin - 1));
}

/*
** get argv and handle '$'
*/

ssize_t			msh_get_argv(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	ssize_t	begin[2];
	ssize_t	ret;
	char	*content[2];

	content[0] = NULL;
	content[1] = NULL;
	begin[0] = len;
	while (msh_check_operator(save, len, "><|\n;"))
	{
		while (msh_check_operator(save, len, "><| \t\n;"))
		{
			ret = 0;
			begin[1] = len;
			while (msh_check_operator(save, len, "$><| \t\'\"\n;"))
				len++;
			if (begin[1] == len && !ft_strchr("$\'\"", save[len]))
				return (0);
			if (begin[1] != len && !(content[1] = ft_substr(save, begin[1], len - begin[1])))
				return (msh_msg_return_val("malloc error", 2, -1));
			if (content[0] && content[1])
				msh_free_set(&content[0], ft_strjoin(content[0], content[1]));
			else if (content[1])
				content[0] = ft_strdup(content[1]);
			msh_free_setnull((void**)&content[1]);
			if (save[len] == '$'
				&& ((ret = msh_get_env(mshinfo, save, len, &content[0])) < 0))
				return (msh_msg_return_val("malloc error", 2, -1));
			len += ret;
			if ((ret = msh_handle_quote(mshinfo, save, len, &content[0])) < 0)
				return (msh_msg_return_val("malloc error", 2, -1));
			len += ret;
		}
		if (content[0])
		{
			msh_free_set(&content[0], msh_strdup_skip_bslash(content[0]));
			if (msh_content_arglst(mshinfo, ft_strdup(content[0])))
				return (msh_msg_return_val("malloc error", 2, -1));
			msh_free_setnull((void**)&content[0]);
		}
		while (msh_isspace(save[len]))
			len++;
	}
	return (len - begin[0]);
}
