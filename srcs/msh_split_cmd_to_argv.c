/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_cmd_to_argv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 09:45:25 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/02 21:11:50 by dhasegaw         ###   ########.fr       */
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

/*
** check existence of file or dir by opening their path
*/

static int	check_existence_file_dir(char *begin, char *cmd, char quate)
{
	char	*path;
	int		fd;
	DIR		*dir_fd;

	if (!(path = ft_substr_skip_bslash(begin, 0, cmd - begin)))
		ft_putendl_fd("msh_exit_by_err", 2);//msh_exit_by_err(mshinfo);
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
	if (!check_existence_file_dir(begin, *cmd, quate))
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
			while (*cmd && !msh_is_space(*cmd) && !(ft_strchr("<>|", *cmd) && !msh_isescaped(cmd, cmd - head)))
				cmd++;
			if (!check_existence_file_dir(begin, cmd, -1))
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
		if (*cmd)
			(*argc)++;
		if (*cmd == '\'' || *cmd == '\"')
		{
			quate = *cmd++;
			while (*cmd && *cmd != quate)
				cmd++;
			cmd++;
			continue ;
		}
		while (*cmd && !((stop = ft_strchr("<>|\t\n\v\f\r \'\"", *cmd)) && !msh_isescaped(cmd, cmd - head)))
			cmd++;
		if (*cmd && stop && (ft_strchr("<>|", *stop)) && !msh_isescaped(cmd, cmd - head))
			(*argc)++;
		if (*cmd && !(stop && ft_strchr("\'\"", *stop) && !msh_isescaped(cmd, cmd - head)))
			cmd++;
	}
}

static int	store_argv_quate(char **ret, char **cmd, int *i, char *head)
{
	char *begin;
	char quate;

	if ((**cmd == '\'' || **cmd == '\"') && !msh_isescaped(*cmd, *cmd - head))
	{
		quate = **cmd;
		(*cmd)++;
		begin = *cmd;
		while (**cmd && **cmd != quate)
			(*cmd)++;
		if (!(ret[++(*i)] = ft_substr(begin, 0, *cmd - begin)))
			ft_putendl_fd("msh_exit_by_err", 2);//msh_exit_by_err(mshinfo);
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

static int	store_argv(char **ret, char **cmd, int *i, char *head)
{
	char *begin;
	char *stop;

	while (**cmd)
	{
		while (**cmd && msh_is_space(**cmd))
			(*cmd)++;
		if (store_argv_quate(ret, &(*cmd), i, head))
			continue ;
		begin = *cmd;
		while (**cmd && !msh_is_space(**cmd)
			&& !((stop = ft_strchr("<>|\'\"", **cmd))
			&& !msh_isescaped(*cmd, *cmd - head)))
			(*cmd)++;
		if (*begin && !(ret[++(*i)] = ft_substr_skip_bslash(begin, 0, *cmd - begin)))
			return (1);
		if ((**cmd && stop && ft_strchr("<>|", *stop)
			&& !msh_isescaped(*cmd, *cmd - head))
			&& !(ret[++(*i)] = ft_substr_skip_bslash(stop, 0, 1)))
			return (1);
		if (**cmd && !(stop && ft_strchr("\'\"", *stop) && !msh_isescaped(*cmd, *cmd - head)))
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
	int		i;

	head = cmd;
	if (check_stdin_redirect(mshinfo, cmd, head))
		ft_putendl_fd("msh_put_errmsg", 2);//msh_put_errmsg(mshinfo);
	count_argc(cmd, argc, head);
	argv = ft_calloc(sizeof(char *), (size_t)(*argc) + 1);
	i = -1;
	if (store_argv(argv, &cmd, &i, head))
		ft_putendl_fd("msh_exit_by_err", 2);//msh_exit_by_err(mshinfo);
	return (argv);
}

/*
** main for test
** gcc -g msh_split_cmd_to_argv.c msh_free_setnull.c msh_char_isescaped.c -I../includes ../libft/libft.a -D TEST_SPLIT
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

int			main(int num, char **var)
{
	int			argc;
	t_mshinfo	mshinfo;
	char		**argv;
	int			i;

	// if (num != 2)
	// 	return (1);
	// argv = msh_split_cmd_to_argv(&mshinfo, "a\>a", &argc);
	argv = msh_split_cmd_to_argv(&mshinfo, var[1], &argc);
	printf("argc: %d\n", argc);
	i = -1;
	while (argv[++i])
		printf("argv[%d]: %s\n", i, argv[i]);
	return (0);
}

#endif
