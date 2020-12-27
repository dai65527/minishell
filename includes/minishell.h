/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:38:24 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/27 12:18:03 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/types.h>

# define MSH_PROMPT	"minishell $ "

# define MSH_NAME "minishell"

/*
**	Struct: s_mshinfo (t_mshinfo)
**
**	Struct to store information for execution of minishell.
**
**	Member
** 	- envlst:		List of enviroment variable.
** 	- arglst:		List of argument of command input.
**					Used in function msh_read_and_exec_cmd.
**	- n_proc:		Number of process in one command execution.
**	- fd_std:		Backups of standard input, output and error output.
**					- fd_std[0]: Standard input.
**					- fd_std[1]: Standard output.
**					- fd_std[2]: Standard error output.
**	- ret_last_cmd:	Return variable of last command. (=$?)
*/

typedef struct	s_mshinfo
{
	t_list		*envlst;
	t_list		*arglst;
	int			n_proc;
	int			fd_std[3];
	int			ret_last_cmd;
	int			has_pipe;
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
int				msh_syntaxcheck(const char *save);
ssize_t			msh_put_syntaxerr(const char token);
pid_t			msh_parse_and_exec_cmd(t_mshinfo *mshinfo, char **save);
int				msh_parse_to_arglst(t_mshinfo *mshinfo, char **save);
int				msh_exec_cmd(t_mshinfo *mshinfo, char **argv, int flg_forked);
pid_t			msh_create_pipe(t_mshinfo *mshinfo, char **argv);
int				msh_create_redirect(char *fname, int redirect_fd,
								int flg_redirect);
void			msh_wait(t_mshinfo *mshinfo, pid_t pid);

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
ssize_t			msh_handle_dollars(char *save, ssize_t len, char ***content);
ssize_t			msh_handle_special_var(t_mshinfo *mshinfo, char *save,
									char ***content, ssize_t len);
ssize_t			msh_handle_redirect(t_mshinfo *mshinfo,
										char *save, ssize_t len);
ssize_t			msh_handle_pipe(char *save, ssize_t len);
ssize_t			msh_handle_quote(t_mshinfo *mshinfo, char *save, ssize_t len,
									char **content);
char			*msh_get_value_from_envlst(t_mshinfo *mshinfo, char **key,
											int flg_quote);
char			*msh_strdup_skip_bslash(char *s);
t_list			*ft_lstget(t_list *lst, int index);
ssize_t			msh_msg_return_val(char *msg, int fd, ssize_t ret);

/*
** minishell utils
*/

int				msh_mshinfo_init(t_mshinfo *mshinfo);
void			msh_mshinfo_free(t_mshinfo *mshinfo);
t_list			*msh_parse_envp(char **envp);
int				msh_env_isvalid(const char *key);
int				msh_env_cmpkey(void *env1, void *env2);
char			**msh_split_cmd_to_argv(t_mshinfo *mshinfo,
										char *cmd, int *argc);
void			msh_free_set(char **dest, char *src);
void			msh_free_argvp(void ***argvp);
int				msh_puterr(char *str1, char *str2, int ret);
void			*msh_puterr_return_null(char *str1, char *str2);

/*
** signal handling
*/

int				msh_initsignal(void);
void			msh_sighandle_putprompt(int sig);
void			msh_sighandle_putendl(int sig);
void			msh_sighandle_donothing(int sig);
void			msh_sighandle_putquit(int sig);

/*
** file discripter utils
*/

int				msh_resetfd(int *fd_std);

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
char			**msh_make_envp(t_list *envlst);

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
int				msh_isspace(char c);

#endif
