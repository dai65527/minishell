/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:45:09 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/17 02:21:29 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	msh_get_env(t_mshinfo *mshinfo, char *save,
							ssize_t len, char **content)
{
	ssize_t	begin;
	ssize_t	ret;
	char	*key;

	if ((ret = msh_handle_dollars(mshinfo, save, len)) != 0)
		return (ret);
	while (msh_check_operator(save, len, "><| \t\'\"\n;"))
	{
		begin = ++len;
		while (msh_check_operator(save, len, "$><| \t\'\"\n;"))
			len++;
		if (!(key = ft_substr(save, begin, len - begin)))
			return (-1);
		msh_free_set(content,
			ft_strjoin(*content, msh_get_value_from_envlst(mshinfo, &key)));
		msh_free_setnull((void**)&key);
		if (!*content)
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

	begin = len;
	ret = 0;
	while (msh_check_operator(save, len, "$><| \t\'\"\n;"))
		len++;
	if (begin == len && save[len] != '$')
		return (0);
	if (!(content = ft_substr(save, begin, len - begin)))
		return (msh_msg_return_val("malloc error", 2, -1));
	if (save[len] == '$'
		&& ((ret = msh_get_env(mshinfo, save, len, &content)) < 0))
		return (msh_msg_return_val("malloc error", 2, -1));
	len += ret;
	msh_free_set(&content, ft_strdup_skip_bslash(content));
	if (msh_content_arglst(mshinfo, content))
		return (msh_msg_return_val("malloc error", 2, -1));
	return (len - begin);
}
