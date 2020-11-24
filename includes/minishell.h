/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:38:24 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/24 18:24:02 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** return values of main function.
*/

# define MSH_EXITSUCCESS

/*
** return values of msh_exec_command function.
*/

# define MSH_RESCMD_SUCCESS	0
# define MSH_RESCMD_FAILURE	1
# define MSH_RESCMD_EXIT	2

/*
** t_mshinfo (= struct s_mshinfo)
** Structure to store information for execution of minishell.
** minishellの実行に必要な情報を格納する構造体。
** 
** member
**  fd_cmdsrc:		コマンドのソースのファイルディスクリプタを格納する。
**					コンソールからの入力(STDIN) -> fd_cmdsrc = 0
**					シェルスクリプト(ファイル)からの入力 -> fd_cmdsrc >= 3
** 	envlst:			環境変数のリスト（環境変数(t_keyval型)を格納するt_list）
** 	ret_last_cmd:	最後に実行したコマンドの返り値。（=$?）
*/

typedef struct  s_mshinfo
{
	t_list      *envlst;
	int         fd_cmdsrc;
	int			ret_last_cmd;
}               t_mshinfo;

/*
** t_keyval (= struct s_keyval)
** Keyvalue data structure which is used to store enviromental variable.
** 環境変数を格納するために使うキーバリュー型構造体。
*/

typedef struct  s_keyval
{
	char        *key;
	char        *val;
}               t_keyval;

#endif
