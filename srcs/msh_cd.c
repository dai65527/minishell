/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 23:27:20 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define CMD "cd"

static char		*get_env(t_mshinfo *mshinfo, char *key)
{
	t_list		*head;
	t_keyval	*env;

	head = mshinfo->envlst;
	while (head)
	{
		env = head->content;
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
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

static int		change_env(t_mshinfo *mshinfo)
{
	t_list		*envlst;
	t_keyval	*env;
	char		*old;
	char		*present;

	envlst = mshinfo->envlst;
	if (!(old = ft_strdup(get_env(mshinfo, "PWD"))))
		return (-1);
	if (!(present = getcwd(NULL, 0)))
		return (-1);
	while (envlst)
	{
		env = envlst->content;
		if (!ft_strncmp("OLDPWD", env->key, ft_strlen("OLDPWD") + 1))
			msh_free_set(&(env->val), old);
		else if (!ft_strncmp("PWD", env->key, ft_strlen("PWD") + 1))
			msh_free_set(&(env->val), present);
		envlst = envlst->next;
	}
	return (0);
}

int				msh_cd(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	int	ret;

	ret = 0;
	if (mshinfo->has_pipe)
		;
	else if (!argv[1])
	{
		if ((chdir(get_env(mshinfo, "HOME"))) < 0)
			ret = -1;
	}
	else if ((chdir(argv[1])) < 0)
		ret = -1;
	if (change_env(mshinfo) < 0)
		ret = -1;
	if (ret < 0)
	{
		mshinfo->ret_last_cmd = (unsigned int)ret;
		if (flg_forked)
			exit(cd_err(argv[1], ret));
		return (cd_err(argv[1], ret));
	}
	mshinfo->ret_last_cmd = ret;
	if (flg_forked)
		exit(ret);
	return (ret);
}
