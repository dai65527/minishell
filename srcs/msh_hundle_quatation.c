/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_hundle_quatation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:56:20 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/12 23:27:05 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

size_t			msh_hundle_dollars(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	t_list	*new;
	char	*content;

	content = NULL;
	if (!ft_strncmp("$?", &save[len], 2)
		&& !(content = ft_strdup(ft_itoa(mshinfo->ret_last_cmd))))
		ft_putendl_fd("msh_put_errmsg", 2);
	else if ((!ft_strncmp("$ ", &save[len], 2) || !ft_strncmp("$\t", save, 2))
			&& !msh_isescaped(save, len) && (!(content = ft_strdup("$"))))
		ft_putendl_fd("msh_put_errmsg", 2);
	else if (!ft_strncmp("$$", &save[len], 2) && !(content = ft_strdup("")))
		ft_putendl_fd("msh_put_errmsg", 2);
	else if ((!ft_strncmp("$", &save[len], 2) || !ft_strncmp("$\"",
			&save[len], 2)) && !(content = ft_strdup("$")))
		ft_putendl_fd("msh_put_errmsg", 2);
	if (content)
	{
		if (!(new = ft_lstnew(content)))
			ft_putendl_fd("msh_put_errmsg", 2);
		ft_lstadd_back(&mshinfo->arglst, new);
		return (2);
	}
	return (0);
}

static size_t	msh_get_env_quate(t_mshinfo *mshinfo, char *save,
									ssize_t len, char **content)
{
	size_t	begin;
	char	*key;

	if (msh_hundle_dollars(mshinfo, save, len))
		return (2);
	begin = ++len;
	while (msh_check_operator(mshinfo, save, len, "$<>|\'\""))
		len++;
	if (!(key = ft_substr(save, begin, len - begin)))
		ft_putendl_fd("msh_put_errmsg", 2);
	msh_free_set(content,
		ft_strjoin(*content, get_value_from_envlst(mshinfo, &key)));
	if (!*content)
		ft_putendl_fd("msh_put_errmsg", 2);
	return (len - (begin - 1));
}

size_t			msh_get_argv_quate(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	size_t	begin1;
	size_t	begin2;
	char	*key;
	char	*content;

	if (!(content = ft_strdup("")))
		ft_putendl_fd("msh_put_errmsg", 2);
	begin1 = len;
	while (msh_check_operator(mshinfo, save, len, "\""))
	{
		begin2 = len;
		while (msh_check_operator(mshinfo, save, len, "$\""))
			len++;
		msh_free_set(&content,
			ft_strjoin(content, ft_substr(save, begin2, len - begin2)));
		if (save[len] == '$')
			len += msh_get_env_quate(mshinfo, save, len, &content);
	}
	if (msh_content_arglst(mshinfo, content))
		ft_putendl_fd("msh_put_errmsg", 2);
	return (len - begin1);
}

size_t			msh_hundle_quate(t_mshinfo *mshinfo, char *save, size_t len)
{
	size_t	begin;
	char	*content;
	t_list	*new;

	if (!ft_strchr("\'\"", save[len]))
		return (0);
	if (save[len] == '\'')
	{
		begin = ++len;
		while (msh_check_operator(mshinfo, save, len, "\'"))
			len++;
		if (save[len] != '\'')
			ft_putendl_fd("quatation is not closing", 2);
		content = ft_substr(save, begin, len++ - begin);
		if (msh_content_arglst(mshinfo, content))
			ft_putendl_fd("msh_put_errmsg", 2);
	}
	else if (save[len] == '\"')
	{
		begin = ++len;
		len += msh_get_argv_quate(mshinfo, save, len);
		if (save[len++] != '\"')
			ft_putendl_fd("quatation is not closing", 2);
	}
	return (len - (begin - 1));
}
