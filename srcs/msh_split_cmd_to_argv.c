/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_cmd_to_argv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 09:45:25 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/11/29 23:08:53 by dhasegaw         ###   ########.fr       */
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

// static char	*ft_substr_skip_bslash(char const *s, t_uint start, size_t len, char quate)
// {
// 	size_t	i;
// 	size_t	s_len;
// 	char	*substr;

// 	s_len = (quate == -1) ? 0 : ft_strlen(s);
// 	if (!s_len)
// 		while (*s)
// 			s_len += (*s++ != '\\') ? 1 : 0;
// 	if (s_len < start)
// 		len = 0;
// 	else if (len > s_len - start)
// 		len = s_len - start;
// 	substr = (char *)malloc(len + 1);
// 	if (!substr)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		if (quate == -1 && s[i + start] != '\\')
// 			substr[i] = s[i + start];
// 		else if (quate != -1)
// 			substr[i] = s[i + start];
// 		i++;
// 	}
// 	substr[len] = 0;
// 	return (substr);
// }

/*
** check existence of file or dir by opening their path
*/

static int	check_existence_file_dir(char *begin, char *cmd, char quate)
{
	char	*path;
	int		fd;
	DIR		*dir_fd;

	if (!(path = ft_substr(begin, 0, cmd - begin)))
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

static int	handle_quate(t_mshinfo *mshinfo, char **cmd)
{
	char	quate;
	char	*path;
	char	*begin;

	quate = **cmd;
	(*cmd)++;
	begin = *cmd;
	while (**cmd && **cmd != quate)
		(*cmd)++;
	if (!check_existence_file_dir(begin, *cmd, quate))
		return (1);
	return (0);
}

/*
** check existence of file or directory checked when '<' is found
*/

static int	check_stdin_redirect(t_mshinfo *mshinfo, char *cmd)
{
	char	*begin;

	while (*cmd)
	{
		if (*cmd == '<')
		{
			cmd++;
			while (*cmd && msh_is_space(*cmd))
				cmd++;
			begin = cmd;
			if (*cmd == '\'' || *cmd == '\"')
			{
				if (handle_quate(mshinfo, &cmd))
					return (1);
				continue ;
			}
			while (*cmd && !msh_is_space(*cmd) && *cmd != '>' && *cmd != '|')
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

static void	count_argc(char *cmd, int *argc)
{
	char	quate;
	char	*stop;

	*argc = 0;
	while (*cmd)
	{
		quate = -1;
		while (*cmd && msh_is_space(*cmd))
			cmd++;
		(*argc)++;
		if (*cmd == '\'' || *cmd == '\"')
		{
			quate = *cmd++;
			while (*cmd && *cmd != quate)
				cmd++;
			cmd++;
			continue ;
		}
		while (*cmd && !(stop = ft_strchr("<>|\t\n\v\f\r \'\"", *cmd)))
			cmd++;
		if (stop && (ft_strchr("<>|", *stop)))
			(*argc)++;
		if (*cmd && stop && !ft_strchr("\'\"", *stop))
			cmd++;
	}
}

static int	store_argv_quate(char **ret, char **cmd, int *i, char *head)
{
	char *begin;
	char quate;

	if ((**cmd == '\'' || **cmd == '\"'))
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
		if (store_argv_quate(ret, cmd, i, head))
			continue ;
		begin = *cmd;
		while (**cmd && !msh_is_space(**cmd)
			&& !(stop = ft_strchr("<>|\'\"", **cmd)))
			(*cmd)++;
		if (!(ret[++(*i)] = ft_substr(begin, 0, *cmd - begin)))
			return (1);
		if (stop && ft_strchr("<>|", *stop)
			&& !(ret[++(*i)] = ft_substr(stop, 0, 1)))
			return (1);
		if (**cmd && stop && !ft_strchr("\'\"", *stop))
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

	if (check_stdin_redirect(mshinfo, cmd))
		ft_putendl_fd("msh_put_errmsg", 2);//msh_put_errmsg(mshinfo);
	count_argc(cmd, argc);
	argv = ft_calloc(sizeof(char *), (size_t)(*argc) + 1);
	head = cmd;
	i = -1;
	if (store_argv(argv, &cmd, &i, head))
		ft_putendl_fd("msh_exit_by_err", 2);//msh_exit_by_err(mshinfo);
	return (argv);
}

/*
** main for test
** gcc msh_split_cmd_to_argv.c msh_free_setnull.c ../libft/libft.a -D TEST_SPLIT
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

	if (num != 2)
		return (1);
	// argv = msh_split_cmd_to_argv(&mshinfo, "a\>a", &argc);
	argv = msh_split_cmd_to_argv(&mshinfo, var[1], &argc);
	printf("argc: %d\n", argc);
	i = -1;
	while (argv[++i])
		printf("argv[%d]: %s\n", i, argv[i]);
	return (0);
}

#endif
