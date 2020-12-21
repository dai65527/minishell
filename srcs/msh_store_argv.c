/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_store_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:36:14 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/21 14:42:43 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static ssize_t	clear_arglst_return_val(t_list **arglst, ssize_t ret)
{
	ft_lstclear(arglst, &free);
	return (ret);
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
		if ((ret = msh_handle_redirect(mshinfo, save, len)) != 0)
			;
		// else if ((ret = msh_handle_pipe(save, len)) != 0)
		// 	*flg = 3;
		else if ((ret = msh_handle_quote(mshinfo, save, len)) != 0)
			;
		else if ((ret = msh_get_argv(mshinfo, save, len)) != 0)
			;
		if (ret < 0)
			return (clear_arglst_return_val(&mshinfo->arglst, -1));
		len += ret;
		while (save[len] && msh_isspace(save[len]))
			len++;
	}
	if (save[len] == '\0')
		*flg = 0;
	else if (save[len] == '\n')
		*flg = 1;
	else if (save[len] == ';')
		*flg = 2;
	else
		*flg = 3;
	return (len);
}
