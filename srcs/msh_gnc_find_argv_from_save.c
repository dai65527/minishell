/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_gnc_find_argv_from_save.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:44:56 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/11 23:50:31 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int			msh_is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

char	*ft_strdup_skip_bslash(char *s)
{
	size_t	i;
	size_t	j;
	size_t	s_len;
	size_t	len;
	char	*substr;
	char 	*head;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	len = s_len;
	head = s;
	while (*s)
	{
		if (*s == '\\' && !msh_isescaped(s, head - s))
			len--;
		s++;
	}
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	j = 0;
	s = head;
	while (i < len && j < s_len)
	{
		if (s[j] != '\\' || (s[j] == '\\' && msh_isescaped(s + j, j)))
			substr[i++] = s[j];
		j++;
	}
	substr[len] = 0;
	return (substr);
}

void	msh_free_set(char **dest, char *src)
{
	free(*dest);
	*dest = src;
}

void		msh_free_argvp(void ***argvp)
{
	int i;

	i = 0;
	while ((*argvp)[i])
	{
		msh_free_setnull(&((*argvp)[i]));
		i++;
	}
	msh_free_setnull((void **)argvp);
	*argvp = NULL;
}

static char	*get_value_from_envlst(t_mshinfo *mshinfo, char **key)
{
	t_list		*head;
	t_keyval	*env;

	if (!*key)
	{
		msh_free_setnull((void**)key);
		return ("");
	}
	head = mshinfo->envlst;
	while (head)
	{
		env = head->content;
		if (!ft_strncmp(env->key, *key, ft_strlen(*key) + 1))
		{
			msh_free_setnull((void**)key);
			return (env->val);
		}
		head = head->next;
	}
	msh_free_setnull((void**)key);
	return ("");
}

static size_t	msh_hundle_dollars(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	t_list	*new;
	char	*content;

	content = NULL;
	if (!ft_strncmp("$?", &save[len], 2)
		&& !(content = ft_strdup(ft_itoa(mshinfo->ret_last_cmd))))
			ft_putendl_fd("msh_put_errmsg", 2);
	else if ((!ft_strncmp("$ ", &save[len], 2) || !ft_strncmp("$\t", save, 2))
				&& !msh_isescaped(save, len) && (!(content = ft_strdup("$"))))
			ft_putendl_fd("msh_put_errmsg", 2);
	else if (!ft_strncmp("$$", &save[len], 2) && !(content = ft_strdup("")))
			ft_putendl_fd("msh_put_errmsg", 2);
	else if (!ft_strncmp("$", &save[len], 2) && !(content = ft_strdup("$")))
			ft_putendl_fd("msh_put_errmsg", 2);
	if (content)
	{
		if (!(new = ft_lstnew(content)))
			ft_putendl_fd("msh_put_errmsg", 2);
		ft_lstadd_back(&mshinfo->arglst, new);
		return (2);
	}
	return (0);
}

size_t	msh_hundle_redirect_pipe(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	size_t	begin;

	begin = len;
	if (!ft_strncmp(&save[len], ">>", 2))
	{		
		ft_putendl_fd(">>", 1);
		len += 2;
		// len += hundle_append(mshinfo, &save[len], len);
	}
	else if (save[len] == '>')
	{
		ft_putendl_fd(">", 1);
		len++;
		// len += hundle_write(mshinfo, &save[len], len);
	}
	else if (save[len] == '<')
	{
		ft_putendl_fd("<", 1);
		len++;
		// len += hundle_read(mshinfo, &save[len], len);
	}
	else if (save[len] == '|')
	{
		ft_putendl_fd("|", 1);
		len++;
		// len += hundle_pipe(mshinfo, &save[len], len);
	}
	return (len - begin);
}

int		msh_check_operator(t_mshinfo *mshinfo,
	char *save, ssize_t len, char *operator)
{
	if (save[len] && !(ft_strchr(operator, save[len])
		&& !msh_isescaped(&save[len], len)))
		return (1);
	else
		return (0);
}

size_t	msh_get_argv(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	size_t	begin1;
	size_t	begin2;
	char	*key;
	char	*content;
	t_list	*new;

	begin1 = len;
	while (msh_check_operator(mshinfo, save, len, "$><| \t\'\"\n;"))
		len++;
	if (begin1 == len && save[len] != '$')
		return (0);
	if (!(content = ft_strdup("")))
		ft_putendl_fd("msh_put_errmsg", 2);
	msh_free_set(&content,
		ft_strjoin(content, ft_substr(save, begin1, len - begin1)));
	if (save[len] == '$')
	{
		if (msh_hundle_dollars(mshinfo, save, len))
			return (2);
		while (msh_check_operator(mshinfo, save, len, "><| \t\'\"\n;"))
		{
			begin2 = ++len;
			while (msh_check_operator(mshinfo, save, len, "$><| \t\'\"\n;"))
				len++;
			if (!(key = ft_substr(save, begin2, len- begin2)))
				ft_putendl_fd("msh_put_errmsg", 2);
			msh_free_set(&content,
				ft_strjoin(content, get_value_from_envlst(mshinfo, &key)));
			if (!content)
				ft_putendl_fd("msh_put_errmsg", 2);
		}
	}
	msh_free_set(&content, ft_strdup_skip_bslash(content));
	if (content)
	{
		if (!(new = ft_lstnew(content)))
			ft_putendl_fd("msh_put_errmsg", 2);
		ft_lstadd_back(&mshinfo->arglst, new);
	}
	else
		ft_putendl_fd("msh_put_errmsg", 2);
	return (len - begin1);
}

size_t	msh_get_argv_quate(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	size_t	begin1;
	size_t	begin2;
	char	*key;
	char	*content;
	t_list	*new;

	begin1 = len;
	while (msh_check_operator(mshinfo, save, len, "$\""))
		len++;
	if (begin1 == len)
		return (0);
	if (!(content = ft_strdup("")))
		ft_putendl_fd("msh_put_errmsg", 2);
	msh_free_set(&content,
		ft_strjoin(content, ft_substr(save, begin1, len - begin1)));
	if (save[len] == '$')
	{
		if (msh_hundle_dollars(mshinfo, save, len))
			return (2);
		while (msh_check_operator(mshinfo, save, len, "\""))
		{
			begin2 = ++len;
			while (msh_check_operator(mshinfo, save, len, "$'\""))
				len++;
			if (!(key = ft_substr(save, begin2, len- begin2)))
				ft_putendl_fd("msh_put_errmsg", 2);
			msh_free_set(&content,
				ft_strjoin(content, get_value_from_envlst(mshinfo, &key)));
			if (content)
			{
				if (!(new = ft_lstnew(content)))
					ft_putendl_fd("msh_put_errmsg", 2);
				ft_lstadd_back(&mshinfo->arglst, new);
			}
			else
				ft_putendl_fd("msh_put_errmsg", 2);
		}
	}
	if (content)
	{
		if (!(new = ft_lstnew(content)))
			ft_putendl_fd("msh_put_errmsg", 2);
		ft_lstadd_back(&mshinfo->arglst, new);
	}
	else
		ft_putendl_fd("msh_put_errmsg", 2);
	return (len - begin1);
}

static size_t	msh_hundle_quate(t_mshinfo *mshinfo, char *save, size_t len)
{
	size_t	begin;
	char	*content;

	if (!ft_strchr("\'\"", save[len]))
		return (0);
	if (!(content = ft_strdup("")))
		ft_putendl_fd("msh_put_errmsg", 2);
	begin = len;
	if (save[len] == '\'')
	{
		if (!(content = ft_strdup("")))
			ft_putendl_fd("msh_put_errmsg", 2);
		begin = len;
		while (msh_check_operator(mshinfo, save, len, "\'"))
			len++;
		if (save[len] != '\'')
			ft_putendl_fd("quatation is not closing", 2);
		msh_free_set(&content,
			ft_strjoin(content, ft_substr(save, begin, len - begin)));
		if (!content)
			ft_putendl_fd("msh_put_errmsg", 2);
		return (len - begin);
	}
	else if (save[len] == '\"')
	{
		len += msh_get_argv_quate(mshinfo, save, len);
		if (save[len] != '\'')
			ft_putendl_fd("quatation is not closing", 2);
	}
	return (len - begin);
}

int				msh_hundle_redirect_fd(t_mshinfo *mshinfo, char *save, size_t len)
{
	size_t	begin;

	begin = len;
	while (ft_isdigit(save[len]))
		len++;
	if (!save[len] || (save[len] && !ft_strchr("<>", save[len])))
		return (0);
	if (!ft_strncmp(&save[len], ">>", 2))
	{
		write(1, &save[begin], len - begin);		
		ft_putendl_fd(">>", 1);
		len += 2;
		// len += hundle_append(mshinfo, &save[len], len);
	}
	else if (save[len] == '>')
	{
		write(1, &save[begin], len - begin);
		ft_putendl_fd(">", 1);
		len++;
		// len += hundle_write(mshinfo, &save[len], len);
	}
	else if (save[len] == '<')
	{
		write(1, &save[begin], len - begin);
		ft_putendl_fd("<", 1);
		len++;
		// len += hundle_read(mshinfo, &save[len], len);
	}
	while (save[len] && msh_is_space(save[len]))
		len++;
	return (len - begin);
}

static size_t	store_argv(t_mshinfo *mshinfo, char *save, size_t len)
{
	size_t	ret;
	size_t	begin;
	char	*stop;
	char	*content;
	t_list	*new;

	begin = len;
	while (msh_check_operator(mshinfo, save, len, "\n;"))
	{
		while (save[len] && msh_is_space(save[len]))
			len++;
		len += msh_hundle_redirect_fd(mshinfo, save,len);
		len += msh_hundle_quate(mshinfo, save, len);
		len += msh_get_argv(mshinfo, save, len);
		len += msh_hundle_redirect_pipe(mshinfo, save, len);
	}
	return (len - begin);
}

static size_t	gnc_argvlen(t_mshinfo *mshinfo, char *save, char *head, int *flg_continue)
{
	size_t	len;

	len = 0;
	while (save[len] != '\n')
	{
		if (save[len] == '\0')
		{
			*flg_continue = 1;
			break ;
		}
		if (save[len] == ';')
		{
			if (!msh_isescaped(save + len, len))
				break ;
			ft_memmove(save + len - 1, save + len, ft_strlen(save + len) + 1);
			continue ;
		}
		len += store_argv(mshinfo, save, len);
	}
	return (len);
}

t_list		*ft_lstget(t_list *lst, int index)
{
	while (lst && index--)
		lst = lst->next;
	return (lst);
}

int			arglst_to_argv(t_mshinfo *mshinfo, char **argv)
{
	int i;

	i = 0;
	while (i < ft_lstsize(mshinfo->arglst))
	{
		if (!(argv[i] = ft_strdup(ft_lstget(mshinfo->arglst, i)->content)))
		{
			ft_lstclear(&mshinfo->arglst, &free);
			return (1);
		}
		i++;
	}
	ft_lstclear(&mshinfo->arglst, &free);
	return (0);
}

/*
** saveから'\n' or ';'を探して、
** その手前まで(=コマンド)を抽出し、cmdに格納する
*/

int				msh_gnc_find_argv_from_save(t_mshinfo *mshinfo, char **save)
{
	int		flg_continue;
	size_t	argvlen;
	char	*new_save;
	char	*head;

	head = *save;
	flg_continue = 0;
	argvlen = gnc_argvlen(mshinfo, *save, head, &flg_continue);
	// if (!(argv = ft_calloc(sizeof(char*), ft_lstsize(mshinfo->arglst) + 1)))
	// 	ft_putendl_fd("msh_put_errmsg", 2);
	// if (arglst_to_argv(mshinfo, argv))
	// 	ft_putendl_fd("msh_put_errmsg", 2);
	if (flg_continue)
		return (MSH_CONTINUE);
	new_save = ft_substr(*save, argvlen + 1, ft_strlen(*save) - argvlen - 1);
	if (!new_save)
	{
		msh_free_setnull((void **)save);
		return (!MSH_CONTINUE);
	}
	free(*save);
	*save = new_save;
	return (!MSH_CONTINUE);
}

/*
** gcc msh_mshinfo_init.c msh_parse_envp.c msh_gnc_find_argv_from_save.c msh_free_setnull.c msh_isescaped.c msh_keyval_free.c -I../includes ../libft/libft.a -D ARGV_TEST
** 424行目のsaveの引数でテストできます。
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
	char *save = ft_strdup("1>> $USER a>b 5<c");
	printf("input: %s\n", save);
	printf("---redirect, pipe---\n");
	char **argvs = NULL;
	msh_gnc_find_argv_from_save(&mshinfo, &save);
	if (!(argvs = ft_calloc(sizeof(char*), ft_lstsize(mshinfo.arglst) + 1)))
		ft_putendl_fd("msh_put_errmsg", 2);
	if (arglst_to_argv(&mshinfo, argvs))
		ft_putendl_fd("msh_put_errmsg", 2);
	int i = -1;
	printf("---------argv-------\n");
	while (argvs[++i])
		printf("%s\n", argvs[i]);
}
#endif 