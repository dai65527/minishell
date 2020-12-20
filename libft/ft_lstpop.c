/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 07:36:43 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 08:03:00 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstpop(t_list **lst, void (*del)(void *))
{
	t_list	*prevlast;

	if (lst == NULL || *lst == NULL)
		return ;
	if ((*lst)->next == NULL)
	{
		ft_lstdelone(*lst, del);
		*lst = NULL;
		return ;
	}
	prevlast = *lst;
	while (prevlast->next->next != NULL)
		prevlast = prevlast->next;
	ft_lstdelone(prevlast->next, del);
	prevlast->next = NULL;
}
