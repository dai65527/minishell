/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_cmd_to_argv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 09:45:25 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/09 14:59:45 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** should be global func in utils.c ?
*/

int			msh_is_space(char c)
{
	if (c == ' ' || ('\t' <= c && c <= '\r'))
		return (1);
	return (0);
}


static char	*get_value_from_envlst(t_mshinfo *mshinfo, char *key)
{
	t_list		*head;
	t_keyval	*env;

	// if (!*key)
	// 	return ("");
	head = mshinfo->envlst;
	while (head)
	{
		env = head->content;
		// if (env->key[0] == '\0' && key[0] == '\0')
		// 	return ("");
		if (!ft_strncmp(env->key, key, ft_strlen(env->key)))
			return (env->val);
		head = head->next;
	}
	return ("");
}

static char	*ft_substr_skip_bslash(char *s, t_uint start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	s_len;
	char	*head;
	char	*substr;

	head = s;
	s_len = ft_strlen(s);
	while (*s)
	{
		if (*s == '\\' && !msh_isescaped(s, head - s))
			len--;
		s++;
	}
	if (s_len < start)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	j = 0;
	s = head;
	while (i < len && s[j + start])
	{
		if (s[j + start] != '\\' || (s[j + start] == '\\' && msh_isescaped(s + j + start, j)))
			substr[i++] = s[j + start];
		j++;
	}
	substr[len] = 0;
	return (substr);
}

static char	*ft_strdup_skip_bslash(char *s)
{
	size_t	i;
	size_t	j;
	size_t	s_len;
	size_t	len;
	char	*substr;
	char 	*head;

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

static void	free_set(char **dest, char *src)
{
	free(*dest);
	*dest = src;
}

static int	get_end_env(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (msh_is_space(str[i]) || (ft_strchr("<>|\'\"$", str[i]) && !msh_isescaped(str, i)))
			return (i);
	}
	return (i);
}

static char *unfold_env(t_mshinfo *mshinfo, char **path)
{
	char *ret;
	char *tmp;
	char *str;
	int i;
	int end;

	str = *path;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && !msh_isescaped(&str[i], i))
		{
			if (!(ret = ft_substr(str, 0, i)))
				ft_putendl_fd("malloc error", 2);
			end = get_end_env(&(str[++i]));
			if (!(tmp = ft_substr(&str[i], 0, end)))
				ft_putendl_fd("malloc error", 2);
			// if (!get_value_from_envlst(mshinfo, tmp))
			// {
			// 	msh_free_setnull((void**)&tmp);
			// 	msh_free_setnull((void**)&ret);
			// 	break ;
			// }
			if (*ret)
				free_set(&ret, ft_strjoin(ret, get_value_from_envlst(mshinfo, tmp)));
			else
				ret = ft_strdup(get_value_from_envlst(mshinfo, tmp));
			free_set(&tmp, ft_strdup(&str[i + end]));
			free_set(&ret, ft_strjoin(ret, tmp));
			msh_free_setnull((void**)&tmp);
			msh_free_setnull((void**)path);
			return (ret);
		}
	}
	return (*path);
}

static int	is_dollar_in(char *s)
{
	int i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
	{
		if (s[i] == '$' && !msh_isescaped(&s[i], i))
			return (1);
	}
	return (0);
}

/*
** check existence of file or dir by opening their path
*/

static int	check_existence_file_dir(t_mshinfo *mshinfo, char *begin, char *cmd, char quate)
{
	char	*path;
	int		fd;
	DIR		*dir_fd;

	if (!(path = ft_substr(begin, 0, cmd - begin)))
		ft_putendl_fd("msh_exit_by_err", 2);//msh_exit_by_err(mshinfo);
	if ((quate == '\"' || quate == -1) && is_dollar_in(path))
		free_set(&path, unfold_env(mshinfo, &path));
	free_set(&path, ft_strdup_skip_bslash(path));
	fd = open(path, O_RDONLY);
	dir_fd = opendir(path);
	msh_free_setnull((void **)&path);
	if (fd < 0 && !dir_fd)
		return (0);
	if (fd > 0)
		close(fd);
	if (dir_fd)
		closedir(dir_fd);
	return (1);
}

/*
** handing the quatation in check_stdin_redirect function
*/

static int	handle_quate(t_mshinfo *mshinfo, char **cmd, char *head)
{
	char	quate;
	char	*path;
	char	*begin;

	quate = **cmd;
	(*cmd)++;
	begin = *cmd;
	while (**cmd && !(**cmd == quate && !msh_isescaped(*cmd, *cmd - head)))
		(*cmd)++;
	if (!**cmd)
		ft_putendl_fd("no closing quatation", 2);//error message which tells no closing quatation.
	if (!check_existence_file_dir(mshinfo, begin, *cmd, quate))
		return (1);
	return (0);
}

/*
** check existence of file or directory checked when '<' is found
*/

static int	check_stdin_redirect(t_mshinfo *mshinfo, char *cmd, char *head)
{
	char	*begin;

	while (*cmd)
	{
		if (*cmd == '<' && !msh_isescaped(cmd, cmd - head))
		{
			cmd++;
			while (*cmd && msh_is_space(*cmd))
				cmd++;
			begin = cmd;
			if ((*cmd == '\'' || *cmd == '\"') && !msh_isescaped(cmd, cmd - head))
			{
				if (handle_quate(mshinfo, &cmd, head))
					return (1);
				continue ;
			}
			while (*cmd && !msh_is_space(*cmd) && !(ft_strchr("<>|$", *cmd) && !msh_isescaped(cmd, cmd - head)))
				cmd++;
			if (!check_existence_file_dir(mshinfo, begin, cmd, -1))
				return (1);
		}
		if (*cmd)
			cmd++;
	}
	return (0);
}

/*
** counts the number of argv by space and quatations
** then store the value into argc
*/

static void	count_argc(char *cmd, int *argc, char *head)
{
	char	quate;
	char	*stop;

	*argc = 0;
	while (*cmd)
	{
		quate = -1;
		while (*cmd && msh_is_space(*cmd))
			cmd++;
		if (!ft_strncmp("$?", cmd, 2) && !msh_isescaped(cmd, cmd - head))
		{
			(*argc)++;
			cmd += 2;
			continue ;
		}
		if (!ft_strncmp("$$", cmd, 2) && !msh_isescaped(cmd, cmd - head))
		{
			(*argc)++;
			cmd += 2;
			continue ;
		}
		if (*cmd)
			(*argc)++;
		if (*cmd == '\'' || *cmd == '\"')
		{
			quate = *cmd++;
			while (*cmd && *cmd != quate)
				cmd++;
			if (*cmd)
				cmd++;
			else
				ft_putendl_fd("no closing quatation", 2);//error message tells there is no closing quatation.
			continue ;
		}
		if (*cmd && ft_strchr("\'\"$", *cmd) && !msh_isescaped(cmd, cmd - head))
			cmd++;
		while (*cmd && !msh_is_space(*cmd) && !((stop = ft_strchr("<>|\'\"$", *cmd)) && !msh_isescaped(cmd, cmd - head)))
			cmd++;
		if (*cmd && stop && (ft_strchr("<>|", *stop)) && !msh_isescaped(cmd, cmd - head))
			(*argc)++;
		if (*cmd && !(stop && ft_strchr("\'\"$", *stop) && !msh_isescaped(cmd, cmd - head)))
			cmd++;
	}
}

static int	store_argv_quate(t_mshinfo *mshinfo, char ***ret, char **cmd, char *head)
{
	char *begin;
	char quate;

	if ((**cmd == '\'' || **cmd == '\"') && !msh_isescaped(*cmd, *cmd - head))
	{
		quate = **cmd;
		(*cmd)++;
		if (quate == "\"" && hundle_dollars(mshinfo, &ret, cmd, head))
			return (1);
		begin = *cmd;
		while (**cmd && **cmd != quate)
			(*cmd)++;
		if (!**cmd)
			ft_putendl_fd("no closing quatation", 2);
		if (!(**ret = ft_substr(begin, 0, *cmd - begin)))
			ft_putendl_fd("msh_exit_by_err", 2);//msh_exit_by_err(mshinfo);
		if (quate == '\"' && is_dollar_in(**ret))
			free_set(*ret, unfold_env(mshinfo, *ret));
		free_set(*ret, ft_strdup_skip_bslash(**ret));
		(*ret)++;
		if (**cmd)
			(*cmd)++;
		return (1);
	}
	return (0);
}

/*
** splits char *cmd by space and single/double quatation
** and store them to char **argv
*/

static int	hundle_dollars(t_mshinfo *mshinfo, char ***ret, char **cmd, char *head)
{
		if (!ft_strncmp("$?", *cmd, 2) && !msh_isescaped(*cmd, *cmd - head))
		{
			if (!(**ret = ft_strdup(ft_itoa(mshinfo->ret_last_cmd))))
				ft_putendl_fd("msh_put_errmsg", 2);//msh_put_errmsg(mshinfo);
			(*ret)++;
			*cmd += 2;
			return (1);
		}
		if ((!ft_strncmp("$ ", *cmd, 2) || !ft_strncmp("$\t", *cmd, 2)) && !msh_isescaped(*cmd, *cmd - head))
		{
			if (!(**ret = ft_strdup("$")))
				ft_putendl_fd("msh_put_errmsg", 2);//msh_put_errmsg(mshinfo);
			(*ret)++;
			*cmd += 2;
			return (1);
		}
		if (!ft_strncmp("$$", *cmd, 2)&& !msh_isescaped(*cmd, *cmd - head))
		{
			if (!(**ret = ft_strdup("")))
				ft_putendl_fd("msh_put_errmsg", 2);//msh_put_errmsg(mshinfo);
			(*ret)++;
			*cmd += 2;
			return (1);
		}
		if (!ft_strncmp("$", *cmd, 2)&& !msh_isescaped(*cmd, *cmd - head))
		{
			if (!(**ret = ft_strdup("$")))
				ft_putendl_fd("msh_put_errmsg", 2);//msh_put_errmsg(mshinfo);
			(*ret)++;
			*cmd += 1;
			return (1);
		}
	return (0);
}


static int	store_argv(t_mshinfo *mshinfo, char **ret, char **cmd, char *head)
{
	char	*begin;
	char	*stop;

	while (**cmd)
	{
		while (**cmd && msh_is_space(**cmd))
			(*cmd)++;
		if (hundle_dollars(mshinfo, &ret, cmd, head))
			continue ;
		// if (!ft_strncmp("$?", *cmd, 2) && !msh_isescaped(*cmd, *cmd - head))
		// {
		// 	*ret++ = ft_strdup(ft_itoa(mshinfo->ret_last_cmd));
		// 	*cmd += 2;
		// 	continue ;
		// }
		// if ((!ft_strncmp("$ ", *cmd, 2) || !ft_strncmp("$\t", *cmd, 2)) && !msh_isescaped(*cmd, *cmd - head))
		// {
		// 	*ret++ = ft_strdup("$");
		// 	*cmd += 2;
		// 	continue ;
		// }
		// if (!ft_strncmp("$$", *cmd, 2)&& !msh_isescaped(*cmd, *cmd - head))
		// {
		// 	*ret++ = ft_strdup("");
		// 	*cmd += 2;
		// 	continue ;
		// }
		// if (!ft_strncmp("$", *cmd, 2)&& !msh_isescaped(*cmd, *cmd - head))
		// {
		// 	*ret++ = ft_strdup("$");
		// 	return (0);
		// }
		if (store_argv_quate(mshinfo, &ret, &(*cmd), head))
			continue ;
		begin = *cmd;
		if (**cmd && ft_strchr("\'\"$", **cmd) && !msh_isescaped(*cmd, *cmd - head))
			(*cmd)++;
		while (**cmd && !msh_is_space(**cmd)
			&& !((stop = ft_strchr("<>|\'\"$", **cmd))
			&& !msh_isescaped(*cmd, *cmd - head)))
			(*cmd)++;
		if (*begin && !(*ret = ft_substr(begin, 0, *cmd - begin)))
			return (1);
		// if (*begin && !(*ret = ft_substr_skip_bslash(begin, 0, *cmd - begin)))
		// 	return (1);
		if (is_dollar_in(*ret))
			free_set(ret, unfold_env(mshinfo, ret));
		free_set(ret, ft_strdup_skip_bslash(*ret));
		ret++;
		if ((**cmd && stop && ft_strchr("<>|", *stop)
			&& !msh_isescaped(*cmd, *cmd - head))
			&& !(*ret++ = ft_substr_skip_bslash(stop, 0, 1)))
			return (1);
		if (**cmd && !(stop && ft_strchr("\'\"$", *stop) && !msh_isescaped(*cmd, *cmd - head)))
			(*cmd)++;
	}
	return (0);
}

/*
** count the number of argv and store the value into argc
** split char *cmd by space and single/double quatation
** and store them to char **argv
** before operations mentioned above,
** existence of file or directory checked when '<' is found
** t_mshinfo *mshinfo will be used for error message
*/

char		**msh_split_cmd_to_argv(t_mshinfo *mshinfo, char *cmd, int *argc)
{
	char	**argv;
	char	*head;

	head = cmd;
	if (check_stdin_redirect(mshinfo, cmd, head))
		ft_putendl_fd("msh_put_errmsg", 2);//msh_put_errmsg(mshinfo);
	count_argc(cmd, argc, head);
	argv = ft_calloc(sizeof(char *), (size_t)(*argc) + 1);
	if (store_argv(mshinfo, argv, &cmd, head))
		ft_putendl_fd("msh_exit_by_err", 2);//msh_exit_by_err(mshinfo);
	return (argv);
}

/*
** main for test
** gcc -g msh_split_cmd_to_argv.c msh_free_setnull.c msh_isescaped.c msh_mshinfo_init.c msh_parse_envp.c msh_keyval_free.c -I../includes ../libft/libft.a -D TEST_SPLIT 
**  (W options are not available due to an unused var: msinfo for error message)
** usage:
**	./a.out './a.out < msh_free_setnull.c aaa' <- correct filepath
**	argc: 4
**	argv[0]: ./a.out
**	argv[1]: <
**	argv[2]: msh_free_setnull.c
**	argv[3]: aaa
**
**	./a.out './a.out < "msh_free_setnull.c aaa"' <- invalid filepath
**	msh_put_errmsg                               <- error massage
**	argc: 3
**	argv[0]: ./a.out
**	argv[1]: <
**	argv[2]: msh_free_setnull.c aaa
**
**	./a.out './a.out < ../' <- correct directory path
**	argc: 3
**	argv[0]: ./a.out
**	argv[1]: <
**	argv[2]: ../
*/

#ifdef TEST_SPLIT
# include <stdio.h>

int			main(int num, char **var, char **envp)
{
	int			argc;
	t_mshinfo	mshinfo;
	char		**argv;
	int			i;

	msh_mshinfo_init(&mshinfo);
	mshinfo.envlst = msh_parse_envp(envp);
	// if (argc <= 1)
	// 	mshinfo.fd_cmdsrc = FD_STDIN;
	// else if ((mshinfo.fd_cmdsrc = open(argv[1], O_RDONLY)) < 0)
	// 	return (msh_exit_by_err(&mshinfo));
	// return (msh_loop(&mshinfo));
	// if (num != 2)
	// 	return (1);
	argv = msh_split_cmd_to_argv(&mshinfo, "\'<\'\"$USER\"", &argc);
	// argv = msh_split_cmd_to_argv(&mshinfo, var[1], &argc);
	printf("argc: %d\n", argc);
	i = -1;
	while (argv[++i])
		printf("argv[%d]: %s\n", i, argv[i]);
	return (0);
}

#endif
