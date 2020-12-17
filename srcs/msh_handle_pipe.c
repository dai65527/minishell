/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:57:23 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/17 11:50:30 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** パイプのハンドリングの関数です。
** fdを取らないこと、処理がredirectと違うことから分けました。
** 中身は中野さんにお任せです。
*/

ssize_t			msh_handle_pipe(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	ssize_t		begin;
	t_list		*tmp;

	begin = len;
	if (msh_check_operator(save, len, "|"))
		return (0);
	ft_putendl_fd("|", 1);
	len++;
	// if (!(dnakno special))
	// return (msh_msg_return_val("pipe error", 2, -1));
	tmp = mshinfo->arglst;//-W option対策、無意味です。
	return (len - begin);
}
