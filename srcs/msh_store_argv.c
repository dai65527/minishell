/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_store_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:36:14 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/15 11:28:25 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/*
** store string into linkedlist 'arglst'
** arglst will be converted to char **argv later
*/

int				msh_content_arglst(t_mshinfo *mshinfo, char *content)
{
	t_list	*new;

	if (content)
	{
		if (!(new = ft_lstnew(content)))
			return (1);
		ft_lstadd_back(&mshinfo->arglst, new);
	}
	else
		return (1);
	return (0);
}

static size_t	msh_get_env(t_mshinfo *mshinfo, char *save,
							ssize_t len, char **content)
{
	size_t	begin;
	char	*key;

	if (msh_hundle_dollars(mshinfo, save, len))
		return (2);
	while (msh_check_operator(save, len, "><| \t\'\"\n;"))
	{
		begin = ++len;
		while (msh_check_operator(save, len, "$><| \t\'\"\n;"))
			len++;
		if (!(key = ft_substr(save, begin, len - begin)))
			ft_putendl_fd("msh_put_errmsg", 2);
		msh_free_set(content,
			ft_strjoin(*content, get_value_from_envlst(mshinfo, &key)));
		if (!*content)
			ft_putendl_fd("msh_put_errmsg", 2);
	}
	return (len - (begin - 1));
}

/*
** get argv and hundle '$'
*/

size_t		msh_get_argv(t_mshinfo *mshinfo, char *save, size_t len)
{
	size_t	begin;
	char	*content;

	begin = len;
	while (msh_check_operator(save, len, "$><| \t\'\"\n;"))
		len++;
	if (begin == len && save[len] != '$')
		return (0);
	if (!(content = ft_strdup("")))
		ft_putendl_fd("msh_put_errmsg", 2);
	msh_free_set(&content,
		ft_strjoin(content, ft_substr(save, begin, len - begin)));
	if (save[len] == '$')
		len += msh_get_env(mshinfo, save, len, &content);
	msh_free_set(&content, ft_strdup_skip_bslash(content));
	if (msh_content_arglst(mshinfo, content))
		ft_putendl_fd("msh_put_errmsg", 2);
	return (len - begin);
}

/*
** check are there special character(operator) and are they escaped
*/

int				msh_check_operator(char *save, ssize_t len, char *operator)
{
	if (save[len] && !(ft_strchr(operator, save[len])
		&& !msh_isescaped(&save[len], len)))
		return (1);
	else
		return (0);
}

/*
** store argv and increment len to parse the string from begining to end
*/

size_t			msh_store_argv(t_mshinfo *mshinfo, char *save, size_t len)
{
	size_t	begin;
	size_t	ret;

	begin = len;
	ret = 0;
	while (msh_check_operator(save, len, "\n;"))
	{
		while (save[len] && msh_is_space(save[len]))
			len++;
		if ((ret = msh_hundle_redirect_fd(mshinfo, save, len)) > 0)
			len += ret;
		else if ((ret = msh_hundle_quate(mshinfo, save, len)) > 0)
			len += ret;
		else if ((ret= msh_get_argv(mshinfo, save, len)) > 0)
			len += ret;
		else if ((ret = msh_hundle_redirect_pipe(mshinfo, save, len)) > 0)
			len += ret;
		while (save[len] && msh_is_space(save[len]))
			len++;
	}
	return (len - begin);
}
