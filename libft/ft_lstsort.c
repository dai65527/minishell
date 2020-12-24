/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 13:23:57 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/03 23:12:09 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swapcontent(t_list *lst1, t_list *lst2)
{
	void	*tmp;

	tmp = lst1->content;
	lst1->content = lst2->content;
	lst2->content = tmp;
}

void		ft_lstsort(t_list **lst, int (*cmp)())
{
	int		i;
	int		j;
	int		size;
	t_list	*lst_ptr;

	if (!lst)
		return ;
	size = ft_lstsize(*lst);
	lst_ptr = *lst;
	i = 0;
	while (i < size)
	{
		lst_ptr = *lst;
		j = 0;
		while (j < size - i - 1)
		{
			if ((*cmp)(lst_ptr->content, (lst_ptr->next)->content) > 0)
				swapcontent(lst_ptr, lst_ptr->next);
			lst_ptr = lst_ptr->next;
			j++;
		}
		i++;
	}
}
