/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 00:09:28 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

#define CMD "cd"
#define HOME "HOME"

static char		*get_home_from_envlst(t_mshinfo *mshinfo)
{
	t_list		*head;
	t_keyval	*env;

	head = mshinfo->envlst;
	while (head)
	{
		env = head->content;
		if (!ft_strncmp(env->key, HOME, ft_strlen(HOME) + 1))
			return (env->val);
		head = head->next;
	}
	return (NULL);
}

int				msh_cd(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	ft_putendl_fd(get_home_from_envlst(mshinfo), 1);
	char *key = ft_strdup(HOME);
	if (mshinfo->has_pipe)
		;
	else if (!argv[1] && (chdir(msh_get_value_from_envlst(mshinfo, &key)) < 0))
	// else if (!argv[1] && (chdir(get_home_from_envlst(mshinfo)) < 0))
	{
		mshinfo->ret_last_cmd = 1;
		if (flg_forked)
			exit(msh_puterr(MSH_NAME, CMD, -1));
		return (msh_puterr(MSH_NAME, CMD, -1));
	}
	else if ((chdir(argv[1])) < 0)
	{
		mshinfo->ret_last_cmd = 1;
		if (flg_forked)
			exit(msh_puterr(MSH_NAME, CMD, -1));
		return (msh_puterr(MSH_NAME, CMD, -1));
	}
	mshinfo->ret_last_cmd = 0;
	if (flg_forked)
		exit(0);
	return (0);
}
