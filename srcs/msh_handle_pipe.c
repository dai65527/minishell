/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:57:23 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/21 12:07:49 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** パイプのハンドリングの関数です。
** fdを取らないこと、処理がredirectと違うことから分けました。
** 中身は中野さんにお任せです。
**
** => 返り値が0でなければflgを立てるだけに変更します。(20.12.20 中野)
*/

ssize_t			msh_handle_pipe(char *save, ssize_t len)
{
	if (msh_check_operator(save, len, "|"))
		return (0);
	return (1);
}
