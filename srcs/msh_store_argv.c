/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_store_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:36:14 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/27 16:03:06 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static ssize_t	clear_arglst_return_val(t_list **arglst, ssize_t ret)
{
	ft_lstclear(arglst, &free);
	return (ret);
}

static int		setflg(char c)
{
	if (c == '\0')
		return (0);
	else if (c == '\n')
		return (1);
	else if (c == ';')
		return (2);
	return (3);
}

/*
** store argv and increment len to parse the string from begining to end
** flg == 0 -> continue
** flg == 1 -> \n end
** flg == 2 -> ; end
** flg == 3 -> pipe
*/

ssize_t			msh_store_argv(t_mshinfo *mshinfo, char *save, int *flg)
{
	ssize_t	len;
	ssize_t	ret;

	len = 0;
	while (msh_check_operator(save, len, "\n;|"))
	{
		while (save[len] && msh_isspace(save[len]))
			len++;
		if (((ret = msh_handle_redirect(mshinfo, save, len)) != 0)
			|| ((ret = msh_get_argv(mshinfo, save, len)) != 0))
		{
			if (ret < 0)
				return (clear_arglst_return_val(&mshinfo->arglst, -1));
			len += ret;
		}
		while (save[len] && msh_isspace(save[len]))
			len++;
	}
	*flg = setflg(save[len]);
	return (len);
}
