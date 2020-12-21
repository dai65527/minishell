/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_find_and_copy_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:21:28 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 10:39:59 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/errno.h>
#include "minishell.h"

static void	msh_free_strs(char **strs)
{
	int		i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

static char	**make_pathv_from_envlst(t_list *envlst)
{
	char		**pathv;
	t_keyval	*env;

	while (envlst)
	{
		env = (t_keyval *)envlst->content;
		if (!ft_strncmp(env->key, "PATH", 5))
			return (ft_split(env->val, ':'));
		envlst = envlst->next;
	}
	pathv = (char **)malloc(sizeof(char *));
	*pathv = NULL;
	return (pathv);
}

static int	find_cmd_from_pathdir(char *cmd, char *dname, char *path)
{
	DIR				*dp;
	struct dirent	*dent;

	errno = 0;
	if (!(dp = opendir(dname)))
		return (0);
	while ((dent = readdir(dp)))
	{
		if (!ft_strncmp(dent->d_name, cmd, PATH_MAX))
		{
			if (ft_strlcpy(path, dname, PATH_MAX) >= PATH_MAX
				|| ft_strlcat(path, "/", PATH_MAX) >= PATH_MAX
				|| ft_strlcat(path, cmd, PATH_MAX) >= PATH_MAX)
			{
				errno = ENAMETOOLONG;
				return (-1);
			}
			return (1);
		}
	}
	return (0);
}

static int	find_cmd_from_path(char **argv, t_list *envlst, char *path)
{
	int			i;
	int			ret;
	char		**pathv;

	if (!(pathv = make_pathv_from_envlst(envlst)))
		return (-1);
	i = 0;
	while (pathv[i])
	{
		if ((ret = find_cmd_from_pathdir(*argv, pathv[i], path)) < 0)
		{
			msh_free_strs(pathv);
			return (-1);
		}
		else if (ret == 1)
		{
			msh_free_strs(pathv);
			return (0);
		}
		i++;
	}
	msh_free_strs(pathv);
	return (-1);
}

int			msh_find_and_copy_path(char **argv, t_mshinfo *mshinfo, char *path)
{
	if (ft_strchr(*argv, '/'))
	{
		if (ft_strlcpy(path, argv[0], PATH_MAX) >= PATH_MAX)
		{
			errno = ENAMETOOLONG;
			return (-1);
		}
	}
	else
	{
		errno = 0;
		if (find_cmd_from_path(argv, mshinfo->envlst, path) < 0)
		{
			if (!errno)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(argv[0], 2);
				ft_putstr_fd(" :command not found\n", 2);
			}
			return (-1);
		}
	}
	return (0);
}
