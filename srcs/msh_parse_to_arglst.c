/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_to_arglst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:44:56 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/28 23:10:42 by dhasegaw         ###   ########.fr       */
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
** saveから'\n' or ';'を探して、
** その手前まで(=コマンド)を抽出し、cmdに格納する
** flg == 1 -> continue
** flg == 2 -> pipe
**
** return val
**	-1: error
**	0: continue to read
**	1: ready to exec command
**  2: ready to exec command and seve still have command
**	3: ready to exec piped command
** flg
**	flg == 0 -> continue
**	flg == 1 -> \n end
**	flg == 2 -> ; end
**	flg == 3 -> pipe
*/

int					msh_parse_to_arglst(t_mshinfo *mshinfo, char **save,
										int *flg_gonext)
{
	int		flg;
	ssize_t	argvlen;
	char	*new_save;
	char	*head;

	head = *save;
	flg = 0;
	argvlen = msh_store_argv(mshinfo, *save, &flg, flg_gonext);
	if (argvlen < 0)
		return (-1);
	if (flg == 0)
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
