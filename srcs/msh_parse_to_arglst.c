/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_to_arglst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:44:56 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/20 18:39:07 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "minishell.h"

/*
** get elem from linkedlist by index from the begining
*/

t_list				*ft_lstget(t_list *lst, int index)
{
	while (lst && index--)
		lst = lst->next;
	return (lst);
}

/*
** arglst(linked list of argv) is convereted to char **argv
*/

static int			arglst_to_argv(t_list **arglst, char **argv)
{
	int i;

	i = 0;
	while (i < ft_lstsize(*arglst))
	{
		if (!(argv[i] = ft_strdup(ft_lstget(*arglst, i)->content)))
		{
			ft_lstclear(arglst, &free);
			return (1);
		}
		i++;
	}
	ft_lstclear(arglst, &free);
	return (0);
}

/*
** saveから'\n' or ';'を探して、
** その手前まで(=コマンド)を抽出し、cmdに格納する
** flg == 1 -> continue
** flg == 2 -> pipe
**
** return val
**	-1: error
**	0: continue to read
**	1: ready to exec command
**	2: ready to exec piped command
** flg
**	flg == 1 -> continue
**	flg == 2 -> pipe
*/

int					msh_parse_to_arglst(t_mshinfo *mshinfo, char **save)
{
	int		flg;
	ssize_t	argvlen;
	char	*new_save;
	char	*head;

	head = *save;
	flg = 0;
	argvlen = msh_store_argv(mshinfo, *save, &flg);
	if (argvlen < 0)
		return (-1);
	if (flg == 1)
		return (0);
	new_save = ft_substr(*save, argvlen + 1, ft_strlen(*save) - argvlen - 1);
	if (!new_save)
	{
		msh_free_setnull((void **)save);
		return (-1);
	}
	free(*save);
	*save = new_save;
	if (flg == 2)
		return (2);
	return (1);
}

/*
** gcc -Wall -Wextra -Werror msh_mshinfo_init.c msh_parse_envp.c msh_gnc_find_argv_from_save.c msh_free_setnull.c msh_isescaped.c msh_keyval_free.c msh_store_argv.c msh_handle_quote.c msh_isspace.c msh_strdup_skip_bslash.c msh_free_funcs.c msh_get_value_from_envlst.c msh_handle_redirect.c msh_handle_dollars.c msh_handle_pipe.c msh_get_argv.c msh_check_operator.c msh_content_arglst.c msh_msg_return_val.c -I../includes -I../libft ../libft/libft.a -D ARGV_TEST
** 100行目のsaveの引数でテストできます。
*/

#ifdef ARGV_TEST
#include <stdio.h>

int		main(int argc, char **argv, char **envp)
{
	t_mshinfo	mshinfo;

	msh_mshinfo_init(&mshinfo);
	if (!(mshinfo.envlst = msh_parse_envp(envp)))
		{}
		// return (msh_exit_by_err(&mshinfo));
	if (argc <= 1)
		mshinfo.fd_cmdsrc = FD_STDIN;
	else if ((mshinfo.fd_cmdsrc = open(argv[1], O_RDONLY)) < 0)
		{}
		// return (msh_exit_by_err(&mshinfo));
	// char *save = ft_strdup("a$USER<b c$USER12<d 0>e f>g \\32<h a$USER|a \\42>>'a$USER<a|a \\42>>'\"a$USER<a|a \\52>>\"");
	char *save = ft_strdup("a b|b d;c e");
	printf("input: %s\n", save);
	printf("---redirect, pipe---\n");
	char **argvs = NULL;
	int ret = msh_gnc_find_argv_from_save(&mshinfo, &save);
	if (ret < 0)
		return (1);
	if (!(argvs = ft_calloc(sizeof(char*), ft_lstsize(mshinfo.arglst) + 1)))
		ft_putendl_fd("msh_put_errmsg", 2);
	if (arglst_to_argv(&mshinfo.arglst, argvs))
		ft_putendl_fd("msh_put_errmsg", 2);
	int i = -1;
	printf("---------argv-------\n");
	while (argvs[++i])
	{
		printf("%s\n", argvs[i]);
		msh_free_setnull((void**)&argvs[i]);
	}
	free(argvs);
	argvs = NULL;
	ret = msh_gnc_find_argv_from_save(&mshinfo, &save);
	if (ret < 0)
		return (1);
	if (!(argvs = ft_calloc(sizeof(char*), ft_lstsize(mshinfo.arglst) + 1)))
		ft_putendl_fd("msh_put_errmsg", 2);
	if (arglst_to_argv(&mshinfo.arglst, argvs))
		ft_putendl_fd("msh_put_errmsg", 2);
	i = -1;
	printf("---------argv-------\n");
	while (argvs[++i])
	{
		printf("%s\n", argvs[i]);
		msh_free_setnull((void**)&argvs[i]);
	}
	free(argvs);
	argvs = NULL;
	msh_free_setnull((void**)&save);
	return (0);
}
#endif
