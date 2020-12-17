/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_dollars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:50:03 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/17 02:15:35 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** handle specail case for '$'
*/

ssize_t		msh_handle_dollars(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	t_list	*new;
	char	*content;

	content = NULL;
	if (!ft_strncmp("$?", &save[len], 2)
		&& !(content = ft_strdup(ft_itoa(mshinfo->ret_last_cmd))))
		return (-1);
	else if ((!ft_strncmp("$ ", &save[len], 2) || !ft_strncmp("$\t", save, 2))
			&& !msh_isescaped(save, len) && (!(content = ft_strdup("$"))))
		return (-1);
	else if (!ft_strncmp("$$", &save[len], 2) && !(content = ft_strdup("")))
		return (-1);
	else if ((!ft_strncmp("$", &save[len], 2) || !ft_strncmp("$\"",
			&save[len], 2)) && !(content = ft_strdup("$")))
		return (-1);
	if (content)
	{
		if (!(new = ft_lstnew(content)))
			return (-1);
		ft_lstadd_back(&mshinfo->arglst, new);
		return (2);
	}
	return (0);
}
