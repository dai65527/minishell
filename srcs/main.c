/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:37:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/25 10:55:27 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_list	*store_envlst(char **envlst)
{
	t_list	*ret;
	t_list	*new;
	int		i;

	i = -1;
	while (envlst[++i])
	{
		new = ft_lstnew(ft_strdup(envlst[i]));
		ft_lstadd_back(&ret, new);
	}
	return (ret);
}

void			msh_free_setnull(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void			msh_free_args(char **args)
{
	int i;

	i = -1;
	while (args[++i])
	{
		free(args[i]);
		args[i] = NULL;
	}
	free(args);
}

/*
** msh_execute splits args into each command and args
** then check cmd[0] to get cmd (e.g. cd or pwd...),
** and call funcs for cmd (e.g. msh_cd)
*/

int				msh_echo(char **cmd, t_mshinfo *info)
{
	char	**tmp;
	int		i;

	tmp = cmd;
	i = info->fd_cmdsrc;
	return (0);
}

int				msh_cd(char **cmd, t_mshinfo *info)
{
	char	**tmp;
	int		i;

	tmp = cmd;
	i = info->fd_cmdsrc;
	return (0);
}

int				msh_pwd(char **cmd, t_mshinfo *info)
{
	char	**tmp;
	int		i;

	tmp = cmd;
	i = info->fd_cmdsrc;
	return (0);
}

int				msh_export(char **cmd, t_mshinfo *info)
{
	char	**tmp;
	int		i;

	tmp = cmd;
	i = info->fd_cmdsrc;
	return (0);
}

int				msh_unset(char **cmd, t_mshinfo *info)
{
	char	**tmp;
	int		i;

	tmp = cmd;
	i = info->fd_cmdsrc;
	return (0);
}

int				msh_env(char **cmd, t_mshinfo *info)
{
	char	**tmp;
	int		i;

	tmp = cmd;
	i = info->fd_cmdsrc;
	return (0);
}

int				msh_exit(char **cmd, t_mshinfo *info)
{
	char	**tmp;
	int		i;

	tmp = cmd;
	i = info->fd_cmdsrc;
	return (0);
}

static	void	print_not_found(char *cmd_name)
{
	ft_putendl_fd("-minishell: ", 2);
	ft_putendl_fd(cmd_name, 2);
	ft_putendl_fd(": command not found", 2);
}

static	int		msh_execute(char **args, t_mshinfo *info)
{
	char	**cmd;
	int		status;
	int		i;

	status = 0;
	i = -1;
	while (args[++i])
	{
		cmd = ft_split(args[i], ' ');
		if (!ft_strncmp(cmd[0], "echo", 4) && ft_strlen(cmd[0]) == 4)
			status = msh_echo(cmd, info);
		else if (!ft_strncmp(cmd[0], "cd", 2) && ft_strlen(cmd[0]) == 2)
			status = msh_cd(cmd, info);
		else if (!ft_strncmp(cmd[0], "pwd", 3) && ft_strlen(cmd[0]) == 3)
			status = msh_pwd(cmd, info);
		else if (!ft_strncmp(cmd[0], "export", 6) && ft_strlen(cmd[0]) == 6)
			status = msh_export(cmd, info);
		else if (!ft_strncmp(cmd[0], "unset", 5) && ft_strlen(cmd[0]) == 5)
			status = msh_unset(cmd, info);
		else if (!ft_strncmp(cmd[0], "env", 3) && ft_strlen(cmd[0]) == 3)
			status = msh_env(cmd, info);
		else if (!ft_strncmp(cmd[0], "exit", 4) && ft_strlen(cmd[0]) == 4)
			status = msh_exit(cmd, info);
		else
			print_not_found(cmd[0]);
	}
	return (status);
}

/*
** msh_loop shows prompt (>) and get stdin by get_next_line func.
** stdin is split to args by ft_split.
** args passed to msh_execute to parse args
** msh_execute run each cmds and get status to handle the loop
** when status is False, loop ends
*/

static	void	msh_loop(t_mshinfo *info)
{
	char	*line;
	char	**args;
	int		status;

	while (1)
	{
		ft_putstr_fd(">", 1);
		get_next_line(0, &line);
		args = ft_split(line, ';');
		status = msh_execute(args, info);
		free(line);
		free_args(args);
		args = NULL;
		if (!status)
			break ;
	}
}

/*
** 1. check the number of arguments: only argc == 1 is acceptable?
** tmp is only for do compiling at this stage
** envp stored to info.envlst by store_envlst
** msh_loop hundles input from users via stdin
*/

int				main(int argc, char **argv, char **envp)
{
	t_mshinfo	info;
	char		*tmp;

	if (argc != 1)
		return (1);
	tmp = argv[1];
	info.envlst = store_envlst(envp);
	msh_loop(&info);
	return (0);
}
