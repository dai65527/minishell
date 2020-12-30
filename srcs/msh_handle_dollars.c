/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_dollars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:50:03 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/29 23:58:27 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** handle specail env variables of "$?" and "$$"
** We don't have to handle $$ as it's not directed in assginment
** but this func cope with $$ to avoid unwilling behavior of other funcs.
*/

ssize_t			msh_handle_special_var(t_mshinfo *mshinfo, char *save,
									char ***content, ssize_t len)
{
	char	*val;

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

/*
** handling $ special cases for avoiding unwilling behavior of other funcs
*/

ssize_t			msh_handle_dollars(char *save, ssize_t len, char ***content,
									int flg_quote)
{
	char	*val;
	ssize_t	ret;

	ret = 0;
	val = NULL;
	if ((!ft_strncmp("$ ", &save[len], 2) || !ft_strncmp("$\t", &save[len], 2)
	|| !ft_strncmp("$", &save[len], 2)))
		ret = 2;
	else if ((flg_quote && !ft_strncmp("$\"", &save[len], 2))
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
		if (!**content)
			return (-1);
	}
	else
		**content = val;
	return (ret);
}
