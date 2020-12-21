/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_and_exec_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 10:05:38 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 07:06:52 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/*
** arglst(linked list of argv) is convereted to char **argv
*/

static char		**arglst_to_argv(t_list **arglst)
{
	int		i;
	int		lstsize;
	char	**argv;

	lstsize = ft_lstsize(*arglst);
	if (!(argv = (char **)malloc(sizeof(char) * (lstsize + 1))))
	{
		ft_lstclear(arglst, free);
		return (NULL);
	}
	i = 0;
	while (i < lstsize)
	{
		if (!(argv[i] = ft_strdup(ft_lstget(*arglst, i)->content)))
		{
			lstsize = 0;
			while (lstsize < i)
				free(argv[lstsize++]);
			ft_lstclear(arglst, free);
			return (NULL);
		}
		i++;
	}
	ft_lstclear(arglst, free);
	return (0);
}

pid_t		msh_parse_and_exec_cmd(t_mshinfo *mshinfo, char **save)
{
	int		ret;
	char	**argv;
	pid_t	pid;

	while (1)
	{
		ret = msh_parse_to_arglst(mshinfo, save);
		if (ret == 0)		// continue to read
			return (0);
		else if	(ret != 1 && ret != 2)	// has error
			return (-1);
		if (!(argv = arglst_to_argv(&mshinfo->arglst)))
			return (-1);
		if (ret == 1)		// exec command
			break ;
		if (msh_create_pipe(mshinfo, argv) < 0)
			return (-1);
		msh_free_argvp((void ***)(&argv));
	}
	pid = msh_exec_cmd(mshinfo, argv, 0);
	msh_free_argvp((void ***)(&argv));
	return (pid);
}
