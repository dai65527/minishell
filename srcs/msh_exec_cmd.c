/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:42:10 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/25 22:17:48 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** msh_exec_cmd
** 	minishellの各コマンドを実行するための関数
**
** 引数
** 	mshinfo: minishellの情報
** 	cmd: 実行するコマンド
** 	ft_input: 実行コマンドが標準入力として読み取るファイルディスクリプタ
**
** 変数
** 	argc:	argvの個数（コマンド自体（"echo"など）も含む）
** 	argv:	cmdからスペースやタブで区切られて生成される文字列配列を格納する
** 			（コマンド自体（"echo"など）も含む）
**
** 関数
** 	mrt_split_cmd_to_argv:	その名の通りcmdをスペース、タブで分割してargvに格納する
** 	msh_xxx:				コマンドを実行する。
** 	msh_executable:			実行可能ファイル（executable）or shell scriptを実行する。
*/

int			msh_exec_cmd(t_mshinfo *mshinfo, char *cmd, int fd_input)
{
	int		argc;
	char	**argv;

	if (!(argv = mrt_split_cmd_to_argv(cmd, &argc)))
		return (MSH_EXIT_BY_ERR);
	if (!ft_strncmp(argv[0], "echo", ft_strlen("echo") + 1))
		return (msh_echo(argc, argv, mshinfo, fd_input));
	else if (!ft_strncmp(argv[0], "cd", ft_strlen("cd") + 1))
		return (msh_cd(argc, argv, mshinfo, fd_input));
	else if (!ft_strncmp(argv[0], "pwd", ft_strlen("pwd") + 1))
		return (msh_pwd(argc, argv, mshinfo, fd_input));
	else if (!ft_strncmp(argv[0], "export", ft_strlen("export") + 1))
		return (msh_export(argc, argv, mshinfo, fd_input));
	else if (!ft_strncmp(argv[0], "unset", ft_strlen("unset") + 1))
		return (msh_unset(argc, argv, mshinfo, fd_input));
	else if (!ft_strncmp(argv[0], "env", ft_strlen("env") + 1))
		return (msh_env(argc, argv, mshinfo, fd_input));
	else if (!ft_strncmp(argv[0], "exit", ft_strlen("exit") + 1))
		return (msh_exit(argc, argv, mshinfo, fd_input));
	else
		return (msh_executable(argc, argv, mshinfo, fd_input));
}
