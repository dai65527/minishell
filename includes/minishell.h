/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:38:24 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/20 19:30:54 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/types.h>

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
** 	arglst:			argvのリスト
** 	ret_last_cmd:	最後に実行したコマンドの返り値。（=$?）
*/

typedef struct	s_mshinfo
{
	t_list		*envlst;
	t_list		*arglst;
	int			n_proc;
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
int				msh_read_and_exec_cmd(t_mshinfo *mshinfo);
int				msh_parse_and_exec_cmd(t_mshinfo *mshinfo, char **save);
int				msh_parse_to_arglst(t_mshinfo *mshinfo, char **save);
int				msh_exec_cmd(t_mshinfo *mshinfo, char **argv, int flg_forked);
pid_t			msh_create_pipe(t_mshinfo *mshinfo, char **argv);
int				msh_create_redirect(const char *fname, int redirect_fd,
								int flg_redirect);

/*
** msh_get_next_cmd
*/

int				msh_get_next_argv(t_mshinfo *mshinfo, char **cmd, char **save);
int				msh_gnc_find_argv_from_save(t_mshinfo *mshinfo, char **save);
int				msh_gnc_expand_env(t_mshinfo *mshinfo, char **cmd);
void			msh_expand_env_to_str(char *str_new, char *str, t_list *envlst);
int				msh_isenv(char *s, char *envkey, size_t slen);
int				msh_isescaped(char *s, size_t len_from_start);

/*
** msh_gnc_find_argv_from_save
*/
ssize_t			msh_store_argv(t_mshinfo *mshinfo, char *save,
								int *flg_continue);
ssize_t			msh_store_argv_redirect(t_mshinfo *mshinfo, char *save,
										ssize_t len);
ssize_t			msh_get_argv(t_mshinfo *mshinfo, char *save, ssize_t len);
int				msh_content_arglst(t_mshinfo *mshinfo, char *content);
int				msh_check_operator(char *save, ssize_t len, char *operator);
ssize_t			msh_handle_dollars(t_mshinfo *mshinfo, char *save, ssize_t len);
ssize_t			msh_handle_redirect(t_mshinfo *mshinfo,
										char *save, ssize_t len);
ssize_t			msh_handle_pipe(char *save, ssize_t len);
ssize_t			msh_handle_quote(t_mshinfo *mshinfo,
										char *save, ssize_t len);
char			*msh_get_value_from_envlst(t_mshinfo *mshinfo, char **key);
char			*ft_strdup_skip_bslash(char *s);
t_list			*ft_lstget(t_list *lst, int index);
ssize_t			msh_msg_return_val(char *msg, int fd, ssize_t ret);

/*
** minishell utils
*/

t_list			*msh_parse_envp(char **envp);
char			**msh_split_cmd_to_argv(t_mshinfo *mshinfo,
										char *cmd, int *argc);
void			*msh_put_errmsg(t_mshinfo *mshinfo);
void			msh_mshinfo_init(t_mshinfo *mshinfo);
void			msh_mshinfo_free(t_mshinfo *mshinfo);
void			msh_free_set(char **dest, char *src);
void			msh_free_argvp(void ***argvp);
int				msh_puterr(const char *str, int ret);

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

int				msh_create_redirect(const char *fname, int redirect_fd,
										int flg_redirect);

/*
** echo
*/

int				msh_echo(t_mshinfo *mshinfo, char **argv, int flg_forked);

/*
** cd
*/

int				msh_cd(t_mshinfo *mshinfo, char **argv, int flg_forked);

/*
** pwd
*/

int				msh_pwd(t_mshinfo *mshinfo, char **argv, int flg_forked);

/*
** export
*/

int				msh_export(t_mshinfo *mshinfo, char **argv, int flg_forked);

/*
** unset
*/

int				msh_unset(t_mshinfo *mshinfo, char **argv, int flg_forked);

/*
** env
*/

int				msh_env(t_mshinfo *mshinfo, char **argv, int flg_forked);

/*
** exit
*/

int				msh_exit(t_mshinfo *mshinfo, char **argv, int flg_forked);

/*
** exec_exceutable
*/

int				msh_executable(t_mshinfo *mshinfo, char **argv, int flg_forked);
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

/*
** '\'によりエスケープされているかを判定する関数。
*/
int				msh_isescaped(char *s, size_t len_from_start);
int				msh_is_space(char c);

#endif
