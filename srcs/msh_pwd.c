/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 00:54:10 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#define CMD "pwd"

int				msh_pwd(t_mshinfo *mshinfo, int flg_forked)
{
	char buf[PATH_MAX];

	if (!getcwd(buf, PATH_MAX))
	{
		mshinfo->ret_last_cmd = 1;
		if (flg_forked)
			exit(msh_puterr(MSH_NAME, CMD, -1));
		return (msh_puterr(MSH_NAME, CMD, -1));
	}
	ft_putendl_fd(buf, FD_STDOUT);
	mshinfo->ret_last_cmd = 0;
	if (flg_forked)
		exit(0);
	return (0);
}
