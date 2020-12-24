/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/24 02:04:36 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <limits.h>

#define CMD "pwd"

int				msh_pwd(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	char buf[PATH_MAX];

	(void)flg_forked;
	(void)argv[0];
	if (!getcwd(buf, PATH_MAX))
	{
		mshinfo->ret_last_cmd = 1;
		return (msh_puterr(MSH_NAME, CMD, -1));
	}
	ft_putendl_fd(buf, FD_STDOUT);
	mshinfo->ret_last_cmd = 0;
	return (0);
}
