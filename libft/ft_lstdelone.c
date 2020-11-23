/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 09:35:53 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/12 18:13:09 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	(*del)(lst->content);
	free(lst);
}
