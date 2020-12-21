/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:37:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 16:44:02 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

/*
**	main
**
** 変数
** 	- mshinfo:	minishellの情報を詰め込んだ構造体変数以下の関数で共有する
**				詳細はminishell.h参照
**
** 関数
** 	- msh_perse_envp: envpの内容を解析してmshinfo.envlstに格納する
** 	- msh_ext_by_err:
** 		- mallocの失敗等、プログラム実行中のエラーにより終了する（エラーメッセージを出力する）
** 		- mshinfoの内容を適切に開放する。
**  - msh_loop:	minishellのメインループ
*/

int		main(int argc, char **argv, char **envp)
{
	int			ret;
	t_mshinfo	mshinfo;

	msh_mshinfo_init(&mshinfo);
	if (!(mshinfo.envlst = msh_parse_envp(envp)))
		return (msh_puterr("bash", NULL, 1));
	if (argc <= 1)
		mshinfo.fd_cmdsrc = FD_STDIN;
	else if ((mshinfo.fd_cmdsrc = open(argv[1], O_RDONLY)) < 0)
		return (msh_puterr("bash", NULL, 1));
	ret = msh_loop(&mshinfo);
	msh_mshinfo_free(&mshinfo);
	return (ret);
}
