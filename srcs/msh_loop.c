/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:59:01 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/28 17:55:37 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/*
** msh_loop
**
** コマンド待ち受け→実行のループを繰り返す関数
**
** msh_get_next_cmd :
** 	- 標準入力 or シェルスクリプトからコマンドを1つ受け取り、cmdに格納する
** 	- 標準入力に対してはプロンプトを表示する。
** 	- コマンドは改行 or ; で分ける。（パイプやリダイレクトがあった場合はそれも含め1コマンドと認識する）
** 	- Ctrl+C, Ctrl+Dの再現を行う必要あり。
** 	- quote, dquoteを待つ処理が必要。
** 	- 返り値
** 		- MSH_CONTINUE: 正常にコマンドを読み取り、コマンドを実行できる状態。
** 		- MSH_EXIT_BY_CMD: Ctrl+Dによるminishell終了時
** 		- MSH_EXIT_BY_ERR: その他のエラーによるmisnishell終了時（malloc失敗等）
**
** msh_exec_cmd :
** 	- cmdの内容に基づいてコマンドを実行する。
** 	- 返り値
** 		- MSH_CONTINUE: 正常にコマンドの実行を終えて、次のコマンドに移ることができる。
** 		- MSH_EXIT_BY_CMD: exitコマンドによるminishell終了時
** 		- MSH_EXIT_BY_ERR: その他のエラーによるmisnishell終了時（malloc失敗等）
**
** msh_ext_by_cmd :
** 	- comanndからの指令により終了する(エラ〜メッセージ等は出力しない)
** 	- mshinfoの内容を適切に開放する。
**
** msh_ext_by_err :
** 	- mallocの失敗等、プログラム実行中のエラーにより終了する（エラ〜メッセージを出力する）
** 	- mshinfoの内容を適切に開放する。
*/

int		msh_loop(t_mshinfo *mshinfo)
{
	int		ret;
	char	*cmd;
	char	*save;

	save = NULL;
	cmd = NULL;
	while (1)
	{
		if ((ret = (msh_get_next_cmd(mshinfo, &cmd, &save)) != MSH_CONTINUE))
			break ;
		ret = msh_exec_cmd(mshinfo, cmd, FD_STDIN);
		msh_free_setnull((void *)&cmd);
		if (ret != MSH_CONTINUE)
			break ;
	}
	free(save);
	if (ret == MSH_EXIT_BY_ERR)
		return (msh_exit_by_err(mshinfo));
	return (msh_exit_by_cmd(mshinfo));
}
