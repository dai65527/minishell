/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:38:24 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/26 15:08:47 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

/*
** return values of msh_exec_command function.
*/

# define MSH_CONTINUE		0
# define MSH_EXIT_BY_CMD	1
# define MSH_EXIT_BY_ERR	2

/*
** used in msh_get_next_cmd
**
** MSH_PROMPT_NORMAL: waiting for input from stdin
** MSH_PROMPT_NEWLINE: waiting for newline from stdin
** MSH_PROMPT_QUOTE: waiting for single quotation
** MSH_PROMPT_DQUOTE: waiting for double quotation
*/

# define MSH_PROMPT	"minishell $ "

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

typedef struct	s_mshinfo
{
	t_list		*envlst;
	int			fd_cmdsrc;
	int			ret_last_cmd;
}				t_mshinfo;

/*
** t_keyval (= struct s_keyval)
** Keyvalue data structure which is used to store enviromental variable.
** 環境変数を格納するために使うキーバリュー型構造体。
*/

typedef struct	s_keyval
{
	char		*key;
	char		*val;
}				t_keyval;

/*
** minishell core
*/

int				msh_loop(t_mshinfo *mshinfo);
int				msh_exec_cmd(t_mshinfo *mshinfo, char *cmd, int fd_input);

/*
** msh_get_next_cmd
*/

int				msh_get_next_cmd(t_mshinfo *mshinfo, char **cmd, char **save);
int				msh_gnc_find_cmd_from_save(char **cmd, char **save);

/*
** minishell utils
*/

t_list			*msh_parse_envp(char **envp);
char			**mrt_split_cmd_to_argv(char *cmd, int *argc);
void			*msh_put_errmsg(t_mshinfo *mshinfo);
void			msh_mshinfo_init(t_mshinfo *mshinfo);
void			msh_mshinfo_free(t_mshinfo *mshinfo);

/*
** minishell 終了時用の関数
** MEMO
** 	msh_ext_by_cmd : comanndからの指令により終了する(エラ〜メッセージ等は出力しない)
** 	msh_ext_by_err : mallocの失敗等、プログラム実行中のエラーにより終了する（エラ〜メッセージを出力する）
*/

int				msh_exit_by_cmd(t_mshinfo *mshinfo);
int				msh_exit_by_err(t_mshinfo *mshinfo);

/*
** echo
*/

int				msh_echo(int argc, char **argv, t_mshinfo *mshinfo,
							int ft_input);

/*
** cd
*/

int				msh_cd(int argc, char **argv, t_mshinfo *mshinfo,
							int ft_input);

/*
** pwd
*/

int				msh_pwd(int argc, char **argv, t_mshinfo *mshinfo,
							int ft_input);

/*
** export
*/

int				msh_export(int argc, char **argv, t_mshinfo *mshinfo,
							int ft_input);

/*
** unset
*/

int				msh_unset(int argc, char **argv, t_mshinfo *mshinfo,
							int ft_input);

/*
** env
*/

int				msh_env(int argc, char **argv, t_mshinfo *mshinfo,
							int ft_input);

/*
** exit
*/

int				msh_exit(int argc, char **argv, t_mshinfo *mshinfo,
							int ft_input);

/*
** exec_exceutable
*/

int				msh_executable(int argc, char **argv, t_mshinfo *mshinfo,
							int ft_input);

/*
** t_keyval utils
** t_keyval用便利関数
*/

void			msh_keyval_free(void *keyval);

#endif
