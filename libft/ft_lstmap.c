/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 10:22:36 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/08 11:18:12 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*newlst;
	t_list		*newelem;

	if (!lst)
		return (NULL);
	newlst = NULL;
	while (lst)
	{
		newelem = ft_lstnew((*f)(lst->content));
		if (!newelem)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newelem);
		lst = lst->next;
	}
	return (newlst);
}
