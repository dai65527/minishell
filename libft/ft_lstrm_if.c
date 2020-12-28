/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:37:03 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/24 15:31:40 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
**	Function: ft_lstrm_if
**
**	This function remove elements from list if its content is match to the ref.
**	The comparison will be done by function cmp and free of the element will be
**	done by del.
*/

void		ft_lstrm_if(t_list **lst, void *ref, int (*cmp)(),
							void (*del)(void *))
{
	t_list		*lstptr;
	t_list		*lstptr_prev;

	if (!lst || !(*lst))
		return ;
	lstptr = *lst;
	lstptr_prev = NULL;
	while (lstptr)
	{
		if (!(*cmp)(lstptr->content, ref))
		{
			if (lstptr_prev)
				lstptr_prev->next = lstptr->next;
			else
				*lst = lstptr->next;
			ft_lstdelone(lstptr, del);
			lstptr = (lstptr_prev) ? lstptr_prev->next : *lst;
			continue ;
		}
		lstptr_prev = lstptr;
		lstptr = lstptr->next;
	}
}
