/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:56:30 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/29 13:49:25 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** store val into content
*/

static int		store_content(char ***content, char **val)
{
	if (!**content)
		**content = ft_strdup(*val);
	else
		msh_free_set(*content, ft_strjoin(**content, *val));
	msh_free_setnull((void**)val);
	if (!**content)
		return (-1);
	return (0);
}

/*
** get env without quote context
*/

ssize_t			msh_get_env(t_mshinfo *mshinfo, char *save,
							ssize_t len, char **content)
{
	ssize_t	begin;
	ssize_t	ret;
	char	*key;
	char	*val;

	if ((ret = msh_handle_dollars(save, len, &content, 0)) != 0)
		return (ret);
	begin = ++len;
	if ((ret = msh_handle_special_var(mshinfo, save, &content, len)) < 0)
		return (-1);
	if (ret)
		return (ret);
	while (msh_check_operator(save, len, "$><| \\\t\'\"\n;"))
		len++;
	if (!(key = ft_substr(save, begin, len - begin)))
		return (-1);
	if (!(val = msh_get_value_from_envlst(mshinfo, &key, 0)))
		return (len - (begin - 1));
	if (store_content(&content, &val))
		return (-1);
	return (len - (begin - 1));
}
