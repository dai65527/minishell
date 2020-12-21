/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_mshinfo_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:38:44 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 17:02:09 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
** Function: msh_mshinfo_init
**
** Initialize structure mshinfo which stores information needed by working
** minishell. For detail of mshinfo, refer to minishell.h.
*/

void	msh_mshinfo_init(t_mshinfo *mshinfo)
{
	mshinfo->envlst = NULL;
	mshinfo->arglst = NULL;
	mshinfo->n_proc = 0;
	mshinfo->fd_cmdsrc = 0;
	mshinfo->ret_last_cmd = 0;
}
