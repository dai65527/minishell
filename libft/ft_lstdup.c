/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 12:48:11 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 13:21:30 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup(t_list *srclst, void *(*dup)(void *), void (*del)(void *))
{
	t_list		*dstlst;
	t_list		*newelem;
	void		*dstcontent;

	dstlst = NULL;
	while (srclst)
	{
		if (!(dstcontent = (*dup)(srclst->content)))
		{
			ft_lstclear(&dstlst, del);
			return (NULL);
		}
		if (!(newelem = ft_lstnew(dstcontent)))
		{
			(*del)(dstcontent);
			ft_lstclear(&dstlst, del);
			return (NULL);
		}
		ft_lstadd_back(&dstlst, newelem);
		srclst = srclst->next;
	}
	return (dstlst);
}
