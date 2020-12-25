/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 20:13:05 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#define CMD "pwd"

static int		err_return_val(t_mshinfo *mshinfo, int flg_forked)
{
	mshinfo->ret_last_cmd = 1;
	if (flg_forked)
		exit(msh_puterr(MSH_NAME, CMD, -1));
	return (msh_puterr(MSH_NAME, CMD, -1));
}

int				msh_pwd(t_mshinfo *mshinfo, int flg_forked)
{
	char	*buf;
	int		i;

	i = 1;
	if (!(buf = getcwd(NULL, 0)))
		return (err_return_val(mshinfo, flg_forked));
	ft_putendl_fd(buf, FD_STDOUT);
	msh_free_setnull((void**)&buf);
	mshinfo->ret_last_cmd = 0;
	if (flg_forked)
		exit(0);
	return (0);
}
