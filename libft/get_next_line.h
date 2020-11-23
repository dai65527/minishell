/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:21:05 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/29 13:17:03 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif

# ifndef N_FDMAX
#  define N_FDMAX		256
# endif

# define GNL_EXITENDF   0
# define GNL_EXITENDL   1
# define GNL_EXITERR    -1

#endif
