/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_and_exec_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 10:05:38 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 21:13:55 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/*
**	Function: arglst_to_argv
**
**	Convert arglst(linked list of argv) argv.
*/

static char		**arglst_to_argv(t_list **arglst)
{
	int		i;
	int		lstsize;
	char	**argv;

	lstsize = ft_lstsize(*arglst);
	if (!(argv = (char **)malloc(sizeof(char *) * (lstsize + 1))))
	{
		ft_lstclear(arglst, free);
		return (msh_puterr_return_null("minishell", NULL));
	}
	i = 0;
	while (i < lstsize)
	{
		if (!(argv[i] = ft_strdup(ft_lstget(*arglst, i)->content)))
		{
			msh_free_argvp((void ***)(&argv));
			ft_lstclear(arglst, free);
			return (msh_puterr_return_null("minishell", NULL));
		}
		i++;
	}
	argv[lstsize] = NULL;
	ft_lstclear(arglst, free);
	return (argv);
}

/*
**	Sub function: parse_and_exec
**
**	Parse save, make argv and execute function.
**	- Call msh_parse_to_arglst function and get command and arguments in
**	  mshinfo->arglst.
**	- Convert mshinfo->arglst to argv by sub function arglst_to_argv.
**	- If msh_parse_to_arglst returns 0, command has not read enough so return 0
**	  to read more.
**	- Else if msh_parse_to_arglst returns 1 or 2, all command and arguments has
**	  stored in mshinfo->arglst, so break loop and execute command.
**	- If if msh_parse_to_arglst returns 2, it means command has ended by ';' and
**	  still have command to read in save, so fold flg_gonext.
**	- Else, (this means 3 has returned), need to make process for pipe by
**	  calling msh_create_pipe and continue to start of the loop.
*/

static pid_t	parse_and_exec(t_mshinfo *mshinfo, char **save, int *flg_gonext)
{
	int		ret;
	char	**argv;
	pid_t	pid;

	while (1)
	{
		if ((ret = msh_parse_to_arglst(mshinfo, save)) == 0)
			return (0);
		else if (ret < 0)
			return (-1);
		if (!(argv = arglst_to_argv(&mshinfo->arglst)))
			return (-1);
		else if (argv[0] == NULL)
			return (-1);
		if (ret == 1 || ret == 2)
			break ;
		if (msh_create_pipe(mshinfo, argv) < 0)
			return (-1);
		msh_free_argvp((void ***)(&argv));
	}
	if (ret == 2)
		*flg_gonext = 0;
	pid = msh_exec_cmd(mshinfo, argv, 0);
	msh_free_argvp((void ***)(&argv));
	return (pid ? pid : -1);
}

/*
**	Function: msh_parse_and_exec_cmd
**
**	This function is loop of parse, exec and wait.
**	If parse_and_exec function retuns 0, it means save should not read enough
**	so returns 0 to read more from command sourse.
**	Else, wait for processes which forked in parse_and_exec function.
**	When all process has ended, continue to read from next command unless
**	flg_gonext is 0. (This means save stil contains command to be executed)
*/

int				msh_parse_and_exec_cmd(t_mshinfo *mshinfo, char **save)
{
	pid_t	pid;
	int		flg_gonext;

	while (1)
	{
		flg_gonext = 1;
		if ((pid = parse_and_exec(mshinfo, save, &flg_gonext)) == 0)
			return (0);
		msh_resetfd(mshinfo->fd_std);
		msh_wait(mshinfo, pid);
		if (flg_gonext)
			return (1);
	}
}
