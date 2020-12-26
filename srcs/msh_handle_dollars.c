/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_dollars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:50:03 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/27 03:28:56 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** handle specail case for '$'
*/

ssize_t			msh_handle_special_var(t_mshinfo *mshinfo, char *save,
									char ***content, ssize_t len)
{
	char	*val;
	ssize_t	begin;

	begin = len;
	if (!ft_strchr("?$", save[len]))
		return (0);
	if (save[len] == '?' && (!(val = ft_itoa(mshinfo->ret_last_cmd))))
		return (-1);
	if (save[len] == '$' && (!(val = ft_strdup("$$"))))
		return (-1);
	if (!**content)
		**content = ft_strdup(val);
	else
		msh_free_set(*content, ft_strjoin(**content, val));
	msh_free_setnull((void**)&val);
	if (!**content)
		return (-1);
	return (2);
}

ssize_t			msh_handle_dollars(char *save, ssize_t len, char ***content)
{
	char	*val;
	ssize_t	ret;

	if (save[len] != '$')
		return (0);
	ret = 0;
	val = NULL;
	if ((!ft_strncmp("$ ", &save[len], 2) || !ft_strncmp("$\t", &save[len], 2)
	|| !ft_strncmp("$", &save[len], 2)))
		ret = 2;
	else if (!ft_strncmp("$\"", &save[len], 2)
	|| !ft_strncmp("$\n", &save[len], 2) || !ft_strncmp("$;", &save[len], 2))
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
