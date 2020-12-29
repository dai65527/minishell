/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/29 16:09:32 by dhasegaw         ###   ########.fr       */
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

static int		change_add_env(t_mshinfo *mshinfo, char *old, char *present)
{
	t_keyval	*newenv_old;
	t_keyval	*newenv_present;

	msh_free_set(&old, ft_strjoin("OLDPWD=", old));
	if (!old)
		return (-1);
	if (!(newenv_old = msh_create_newenv(old)))
		return (-1);
	if (!msh_change_env_val(mshinfo->envlst, newenv_old))
		if (msh_add_new_env(mshinfo, newenv_old))
			return (-1);
	msh_free_set(&present, ft_strjoin("PWD=", present));
	if (!present)
		return (-1);
	if (!(newenv_present = msh_create_newenv(present)))
		return (-1);
	if (!msh_change_env_val(mshinfo->envlst, newenv_old))
		if (msh_add_new_env(mshinfo, newenv_present))
			return (-1);
	return (0);
}

static int		modify_env(t_mshinfo *mshinfo)
{
	// t_list		*envlst;
	// t_keyval	*env;
	char		*old;
	char		*present;

	// envlst = mshinfo->envlst;
	old = get_env(mshinfo, "PWD") ?
		ft_strdup(get_env(mshinfo, "PWD")) : ft_strdup("");
	if (!old)
		return (-1);
	if (!(present = getcwd(NULL, 0)))
		return (-1);
	if (change_add_env(mshinfo, old, present))
		return (-1);
	// while (!flg && envlst)
	// {
	// 	env = envlst->content;
	// 	if (flg % 2 && !ft_strncmp("OLDPWD", env->key, ft_strlen("OLDPWD") + 1))
	// 		msh_free_set(&(env->val), old);
	// 	else if (flg >= 2 && !ft_strncmp("PWD", env->key, ft_strlen("PWD") + 1))
	// 		msh_free_set(&(env->val), present);
	// 	envlst = envlst->next;
	// }
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
	if (modify_env(mshinfo) < 0)
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
