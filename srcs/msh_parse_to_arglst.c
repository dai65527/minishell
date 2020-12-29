/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_to_arglst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:44:56 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/29 21:05:02 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
** Find '\n' or ';' from save and store the string just before it to cmd.
**
** return val
**	-1: error
**	0: continue to read
**	1: ready to exec command
**  2: ready to exec command and seve still have command
**	3: ready to exec piped command
**	4: empty command
** flg
**	flg == 0 -> continue
**	flg == 1 -> \n end
**	flg == 2 -> ; end
**	flg == 3 -> pipe
**	flg == 4 -> empty command
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
	if (flg == 0 || flg == 4)
		return (flg);
	new_save = ft_substr(*save, argvlen + 1, ft_strlen(*save) - argvlen - 1);
	if (!new_save)
	{
		msh_free_setnull((void **)save);
		return (-1);
	}
	free(*save);
	*save = new_save;
	return (flg);
}
