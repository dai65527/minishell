/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:18:04 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/20 18:56:04 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
** to get only one argv after redirect,
** msh_store_argv is modified.
*/

static ssize_t	store_argv_redirect(t_mshinfo *mshinfo, char *save,
										ssize_t len)
{
	ssize_t	begin;
	ssize_t	ret;

	begin = len;
	ret = 0;
	while (msh_check_operator(save, len, "\n;<>|"))
	{
		while (save[len] && msh_is_space(save[len]))
			len++;
		if ((ret = msh_handle_quote(mshinfo, save, len)) != 0)
			return (ret > 0 ? len + ret - begin : -1);
		else if ((ret = msh_get_argv(mshinfo, save, len)) != 0)
			return (ret > 0 ? len + ret - begin : -1);
		while (save[len] && msh_is_space(save[len]))
			len++;
	}
	return (-1);
}

/*
** for use of hundling redirection,
** delete last elem of arglst and set null for prev elem's next;
*/

static	void	ft_lstpop(t_list **arglst)
{
	t_list *last;

	last = ft_lstlast(*arglst);
	ft_lstdelone(last, &free);
	last = NULL;
	ft_lstget(*arglst, ft_lstsize(*arglst) - 2)->next = NULL;
}

/*
** redirect, pipeごとのflagを立てることと、fdの調整をします。
** fdは指定がない場合、各redirectごとのデフォルトの0か１に調整します。
*/

static int		get_flg_redirect(char *save, ssize_t len, ssize_t begin,
									int *fd)
{
	if (!ft_strncmp(&save[len], ">>", 2))
	{
		if (begin == len && *fd == 0)
			*fd = 1;
		return (0);
	}
	else if (save[len] == '>')
	{
		if (begin == len && *fd == 0)
			*fd = 1;
		return (1);
	}
	else if (save[len] == '<')
	{
		if (begin == len && *fd == 0)
			*fd = 0;
		return (2);
	}
	return (-1);
}

/*
** hundling number + redirect as fd + redirect
** and get the next argv then delete the argv
** flg_redirect
**	0: append
**	1: write
**	2: read
*/

ssize_t			msh_handle_redirect(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	ssize_t	begin;
	ssize_t	ret;
	int		fd;
	t_list	*last;
	int		flg_redirect;

	begin = len;
	fd = 0;
	while (ft_isdigit(save[len]))
	{
		fd = fd * 10 + (save[len] - '0');
		len++;
	}
	if (msh_check_operator(save, len, "<>"))
		return (0);
	flg_redirect = get_flg_redirect(save, len, begin, &fd);
	len += (flg_redirect == 0) ? 2 : 1;
	if ((ret = store_argv_redirect(mshinfo, save, len)) < 0)
		return (msh_msg_return_val("syntax error", 2, -1));
	last = ft_lstlast(mshinfo->arglst);
	ret = msh_create_redirect(last->content, fd, flg_redirect);
	if (ret < 0)
		return (msh_msg_return_val("redirect error", 2, -1));
	else if (ret == 1)
		mshinfo->n_proc++;
	return (len + ret - begin);
}
