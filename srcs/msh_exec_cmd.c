/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:42:10 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/26 07:58:23 by dnakano          ###   ########.fr       */
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
**
** 変数
** 	argc:	argvの個数（コマンド自体（"echo"など）も含む）
** 	argv:	cmdからスペースやタブで区切られて生成される文字列配列を格納する
** 			（コマンド自体（"echo"など）も含む）
**
** 関数
** 	msh_split_cmd_to_argv:	その名の通りcmdをスペース、タブで分割してargvに格納する
** 	msh_xxx:				コマンドを実行する。
** 	msh_executable:			実行可能ファイル（executable）or shell scriptを実行する。
*/

int			msh_exec_cmd(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	if (!msh_strcmp_inlower(argv[0], "echo"))
		return (msh_echo(mshinfo, argv, flg_forked));
	else if (!ft_strncmp(argv[0], "cd", 3))
		return (msh_cd(mshinfo, argv, flg_forked));
	else if (!msh_strcmp_inlower(argv[0], "pwd"))
		return (msh_pwd(mshinfo, flg_forked));
	else if (!ft_strncmp(argv[0], "export", 7))
		return (msh_export(mshinfo, argv, flg_forked));
	else if (!ft_strncmp(argv[0], "unset", 6))
		return (msh_unset(mshinfo, argv, flg_forked));
	else if (!msh_strcmp_inlower(argv[0], "env"))
		return (msh_env(mshinfo, argv, flg_forked));
	else if (!ft_strncmp(argv[0], "exit", 5))
		return (msh_exit(mshinfo, argv, flg_forked));
	return (msh_executable(mshinfo, argv, flg_forked));
}
