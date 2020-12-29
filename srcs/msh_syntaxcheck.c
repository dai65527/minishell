/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_syntaxcheck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 08:44:34 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/29 10:50:06 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "minishell.h"

#define F_FIRST		1
#define F_ESCAPED	2

static int		initialcheck(const char *save)
{
	size_t		len;

	len = ft_strlen(save);
	if (len == 0 || save[len - 1] != '\n')
		return (0);
	return (1);
}

int				msh_syntaxcheck(const char *save)
{
	uint32_t	flg;
	size_t		len;
	ssize_t		ret;

	if (initialcheck(save) == 0)
		return (0);
	flg = F_FIRST;
	len = 0;
	while (save[len] != '\0')
	{
		while (msh_isspace(save[len]))
			len++;
		if (((ret = msh_syntaxcheck_quote(save, len, &flg)) != 0)
			|| ((ret = msh_syntaxcheck_redirect(save, len, &flg)) != 0)
			|| ((ret = msh_syntaxcheck_pipe(save, len, &flg)) != 0))
		{
			if (ret < 0)
				return (-1);
		}
		else if (msh_syntaxcheck_flag(save, len, &flg) != 0)
			return (-1);
		len = (ret == 0) ? (len + 1) : (len + ret);
	}
	return (1);
}
