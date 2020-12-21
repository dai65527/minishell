/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_make_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:53:58 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 13:09:59 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static char	**make_envp_errend(char **envp, int n)
{
	int		i;

	i = 0;
	while (i < n)
		free(envp[i++]);
	free(envp);
	return (NULL);
}

char		**msh_make_envp(t_list *envlst)
{
	int			i;
	int			size;
	int			len;
	t_keyval	*env;
	char		**envp;

	size = ft_lstsize(envlst);
	if (!(envp = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		env = (t_keyval *)envlst->content;
		len = ft_strlen(env->key) + ft_strlen(env->val) + 2;
		if (!(envp[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (make_envp_errend(envp, i));
		ft_strlcpy(envp[i], env->key, len + 1);
		ft_strlcat(envp[i], "=", len + 1);
		ft_strlcat(envp[i], env->val, len + 1);
		envlst = envlst->next;
		i++;
	}
	envp[size] = NULL;
	return (envp);
}
