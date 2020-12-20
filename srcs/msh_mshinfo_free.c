/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_mshinfo_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:44:56 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/20 18:14:02 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*
** msh_mshinfo_free
**
** free contents of structure mshinfo.
** 構造体msh_infoのフリー用関数
*/

void	msh_mshinfo_free(t_mshinfo *mshinfo)
{
	ft_lstclear(&mshinfo->envlst, msh_keyval_free);
	if (mshinfo->fd_cmdsrc > 2)
		close(mshinfo->fd_cmdsrc);
}
