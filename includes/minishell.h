/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:38:24 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/25 10:42:27 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "libft.h"

typedef struct  s_mshinfo
{
	t_list		*envlst;
	int			fd_cmdsrc;
	int			ret_last_cmd;
}				t_mshinfo;

#endif
