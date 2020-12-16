/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_msg_return_val.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:54:06 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/17 01:10:05 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>

/*
** function to handle msg, fd, return value at the same time
*/

ssize_t		msh_msg_return_val(char *msg, int fd, ssize_t ret)
{
	ft_putendl_fd(msg, fd);
	return (ret);
}
