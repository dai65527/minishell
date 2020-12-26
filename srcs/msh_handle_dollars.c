/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_dollars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:50:03 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/26 22:00:30 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** handle specail case for '$'
*/

ssize_t			msh_handle_dollars(t_mshinfo *mshinfo, char *save, ssize_t len,
									char ***content)
{
	char	*val;
	ssize_t	ret;

	(void)mshinfo;
	if (save[len] != '$')
		return (0);
	ret = 0;
	val = NULL;
	if ((!ft_strncmp("$ ", &save[len], 2) || !ft_strncmp("$\t", &save[len], 2)
	|| !ft_strncmp("$", &save[len], 2)))
		ret = 2;
	else if (!ft_strncmp("$\"", &save[len], 2))
		ret = 1;
	if (!ret)
		return (0);
	if (ret && !(val = ft_strdup("$")))
		return (-1);
	if (**content)
	{
		msh_free_set(*content, ft_strjoin(**content, val));
		msh_free_setnull((void**)&val);
	}
	else
		**content = val;
	return (ret);
}
