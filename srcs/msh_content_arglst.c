/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_content_arglst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:23:02 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/20 22:05:02 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** store string into linkedlist 'arglst'
** arglst will be converted to char **argv later
*/

int		msh_content_arglst(t_mshinfo *mshinfo, char *content)
{
	t_list	*new;

	if (!content)
		return (1);
	if (!(new = ft_lstnew(content)))
		return (1);
	ft_lstadd_back(&mshinfo->arglst, new);
	return (0);
}
