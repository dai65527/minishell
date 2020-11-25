/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_mshinfo_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:38:44 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/24 19:45:44 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
** msh_mshinfo_init
**
** initialize structure mshinfo.
** 構造体msh_infoの初期化用関数
*/

void	msh_mshinfo_init(t_mshinfo *mshinfo)
{
	mshinfo->envlst = NULL;
	mshinfo->fd_cmdsrc = 0;
	mshinfo->ret_last_cmd = 0;
}
