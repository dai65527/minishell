/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_argv_redirect_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:18:04 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/16 01:47:29 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/*
** to get only one argv after redirect,
** msh_store_argv is modified.
*/

size_t			msh_store_argv_redirect(t_mshinfo *mshinfo, char *save,
										size_t len)
{
	size_t	begin;
	size_t	ret;

	begin = len;
	ret = 0;
	while (msh_check_operator(save, len, "\n;<>|"))
	{
		while (save[len] && msh_is_space(save[len]))
			len++;
		if ((ret = msh_handle_quate(mshinfo, save, len)) > 0)
			break ;
		else if ((ret = msh_get_argv(mshinfo, save, len)) > 0)
			break ;
		while (save[len] && msh_is_space(save[len]))
			len++;
	}
	return (len + ret - begin);
}

/*
** for use of hundling redirection,
** delete last elem of arglst and set null for prev elem's next;
*/

void			ft_lstpop(t_list **arglst)
{
	t_list *last;

	last = ft_lstlast(*arglst);
	ft_lstdelone(last, &free);
	last = NULL;
	ft_lstget(*arglst, ft_lstsize(*arglst) - 2)->next = NULL;
}

/*
** パイプのハンドリングの関数です。
** fdを取らないこと、処理がredirectと違うことから分けました。
** 中身は中野さんにお任せです。
*/

size_t			msh_handle_pipe(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	size_t		begin;
	t_list		*tmp;

	begin = len;
	if (msh_check_operator(save, len, "|"))
		return (0);
	ft_putendl_fd("|", 1);
	len++;
	// dnakno special!
	tmp = mshinfo->arglst;//-W option対策、無意味です。
	return (len - begin);
}

/*
** redirect, pipeごとのflagを立てることと、fdの調整をします。
** fdは指定がない場合、各redirectごとのデフォルトの0か１に調整します。
*/

static int		get_flg_redirect(char *save, size_t len, size_t begin, int *fd)
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
** 中野さんがリダイレクトとパイプをやっつける関数
** redirect, pipeのフラグ、file discripter, １つ後のargvが引数です。
** 処理にエラーがあれば1, なければ0を返します。
** 暫定的に動作確認のためedirectとpipe fdを出力するようにしています。
*/

int				dnakano_redirect(int flg_redirect_pipe, int fd, char *argv)
{
	ft_putnbr_fd(fd, 1);
	if (flg_redirect_pipe == 0)
		ft_putstr_fd(">>", 1);
	if (flg_redirect_pipe == 1)
		ft_putstr_fd(">", 1);
	if (flg_redirect_pipe == 2)
		ft_putstr_fd("<", 1);
	ft_putendl_fd(argv, 1);
	return (0);
}

/*
** hundling number + redirect as fd + redirect
** and get the next argv then delete the argv
*/

size_t			msh_handle_redirect_fd(t_mshinfo *mshinfo, char *save, size_t len)
{
	size_t	begin;
	size_t	ret;
	int		fd;
	t_list	*last;
	int		flg_redirect_pipe;

	begin = len;
	fd = 0;
	while (ft_isdigit(save[len]))
	{
		fd = fd * 10 + (save[len] - '0');
		len++;
	}
	if (msh_check_operator(save, len, "<>"))
		return (0);
	flg_redirect_pipe = get_flg_redirect(save, len, begin, &fd);
	len += (flg_redirect_pipe == 0) ? 2 : 1;
	if ((ret = msh_store_argv_redirect(mshinfo, save, len)) == 0)
		ft_putendl_fd("syntax error of redirection", 2);//free, exit, close fd etc...
	last = ft_lstlast(mshinfo->arglst);
	if (dnakano_redirect(flg_redirect_pipe, fd, last->content))
		ft_putendl_fd("msh_put_errmsg", 2);//free, exit, close fd etc...
	ft_lstpop(&mshinfo->arglst);
	return (len + ret - begin);
}
