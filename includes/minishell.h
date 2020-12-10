/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:38:24 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/10 20:31:49 by dnakano          ###   ########.fr       */
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
int				msh_exec_cmd(t_mshinfo *mshinfo, char **argv);

/*
** msh_get_next_cmd
*/

int				msh_get_next_cmd(t_mshinfo *mshinfo, char **cmd, char **save);
int				msh_gnc_find_cmd_from_save(char **cmd, char **save);
int				msh_gnc_expand_env(t_mshinfo *mshinfo, char **cmd);
void			msh_expand_env_to_str(char *str_new, char *str, t_list *envlst);
int				msh_isenv(char *s, char *envkey, size_t slen);
int				msh_isescaped(char *s, size_t len_from_start);

/*
** minishell utils
*/

t_list			*msh_parse_envp(char **envp);
char			**msh_make_envp(t_list *envlst);
char			**mrt_split_cmd_to_argv(char *cmd, int *argc);
void			*msh_put_errmsg(t_mshinfo *mshinfo);
void			msh_mshinfo_init(t_mshinfo *mshinfo);
void			msh_mshinfo_free(t_mshinfo *mshinfo);

/*
** file discripter utils
*/

int				msh_backupfd(int *stdfd_backup);
int				msh_resetfd(int *stdfd_backup);
void			msh_closefds(int fd, int *pipe_fd);

/*
** minishell 終了時用の関数
** MEMO
** 	msh_ext_by_cmd : comanndからの指令により終了する(エラ〜メッセージ等は出力しない)
** 	msh_ext_by_err : mallocの失敗等、プログラム実行中のエラーにより終了する（エラ〜メッセージを出力する）
*/

int				msh_exit_by_cmd(t_mshinfo *mshinfo);
int				msh_exit_by_err(t_mshinfo *mshinfo);

/*
** redirect and pipe
*/

int				msh_handle_redirect_and_pipe(char **argv, t_mshinfo *mshinfo);
int				msh_handle_redirect(char **argv);
int				msh_create_redirect_process(char *fname,
								int redirect_fd, int open_option);
int				msh_handle_pipe(char **argv, t_mshinfo *mshinfo);

/*
** echo
*/

int				msh_echo(char **argv, t_mshinfo *mshinfo);

/*
** cd
*/

int				msh_cd(char **argv, t_mshinfo *mshinfo);

/*
** pwd
*/

int				msh_pwd(char **argv, t_mshinfo *mshinfo);

/*
** export
*/

int				msh_export(char **argv, t_mshinfo *mshinfo);

/*
** unset
*/

int				msh_unset(char **argv, t_mshinfo *mshinfo);

/*
** env
*/

int				msh_env(char **argv, t_mshinfo *mshinfo);

/*
** exit
*/

int				msh_exit(char **argv, t_mshinfo *mshinfo);

/*
** exec_exceutable
*/

int				msh_executable(char **argv, t_mshinfo *mshinfo);
int				msh_find_and_copy_path(char **argv, t_mshinfo *mshinfo,
																char *path);

/*
** t_keyval utils
** t_keyval用便利関数
*/

void			msh_keyval_free(void *keyval);

/*
** *ptrをfreeして、*ptr=NULLする便利関数
*/

void			msh_free_setnull(void **ptr);

#endif
