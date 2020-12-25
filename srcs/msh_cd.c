/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 12:26:57 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define CMD "cd"

static char		*get_home_dir(t_mshinfo *mshinfo)
{
	t_list		*head;
	t_keyval	*env;

	head = mshinfo->envlst;
	while (head)
	{
		env = head->content;
		if (!ft_strncmp(env->key, "HOME", ft_strlen("HOME") + 1))
			return (env->val);
		head = head->next;
	}
	return (NULL);
}

static int		cd_err(char *dirname, int ret)
{
	ft_putstr_fd(MSH_NAME, FD_STDERR);
	ft_putstr_fd(": ", FD_STDERR);
	ft_putstr_fd(CMD, FD_STDERR);
	ft_putstr_fd(": ", FD_STDERR);
	if (!dirname)
		ft_putendl_fd("HOME not set", FD_STDERR);
	else
	{
		ft_putstr_fd(dirname, FD_STDERR);
		ft_putstr_fd(": ", FD_STDERR);
		ft_putendl_fd(strerror(errno), FD_STDERR);
	}
	return (ret);
}

int				msh_cd(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	if (mshinfo->has_pipe)
		;
	else if (!argv[1])
	{
		if ((chdir(get_home_dir(mshinfo))) < 0)
		{
			mshinfo->ret_last_cmd = 1;
			if (flg_forked)
				exit(cd_err(NULL, -1));
			return (cd_err(NULL, -1));
		}
	}
	else if ((chdir(argv[1])) < 0)
	{
		mshinfo->ret_last_cmd = 1;
		if (flg_forked)
			exit(cd_err(argv[1], -1));
		return (cd_err(argv[1], -1));
	}
	mshinfo->ret_last_cmd = 0;
	if (flg_forked)
		exit(0);
	return (0);
}
