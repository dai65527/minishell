/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_mshinfo_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:44:56 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 18:03:19 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*
** Function: msh_mshinfo_free
**
** Free or close menbers of structure mshinfo if needed.
*/

void	msh_mshinfo_free(t_mshinfo *mshinfo)
{
	ft_lstclear(&mshinfo->envlst, msh_keyval_free);
	if (mshinfo->fd_cmdsrc != mshinfo->fd_std[0])
		close(mshinfo->fd_cmdsrc);
	close(mshinfo->fd_std[0]);
	close(mshinfo->fd_std[1]);
	close(mshinfo->fd_std[2]);
}
