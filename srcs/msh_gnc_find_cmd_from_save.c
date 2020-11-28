/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_gnc_find_cmd_from_save.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:44:56 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/28 18:36:58 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static size_t	gnc_cmdlen(char *save, int *flg_continue)
{
	size_t	len;

	len = 0;
	while (save[len] != ';' && save[len] != '\n')
	{
		if (save[len] == '\0')
		{
			*flg_continue = 1;
			return (0);
		}
		len++;
	}
	return (len);
}

/*
** saveから'\n' or ';'を探して、
** その手前まで(=コマンド)を抽出し、cmdに格納する
*/

int				msh_gnc_find_cmd_from_save(char **cmd, char **save)
{
	int		flg_continue;
	size_t	cmdlen;
	char	*new_save;

	flg_continue = 0;
	cmdlen = gnc_cmdlen(*save, &flg_continue);
	if (flg_continue)
		return (MSH_CONTINUE);
	if (!(*cmd = ft_substr(*save, 0, cmdlen)))
	{
		msh_free_setnull((void **)save);
		return (!MSH_CONTINUE);
	}
	new_save = ft_substr(*save, cmdlen + 1, ft_strlen(*save) - cmdlen - 1);
	if (!new_save)
	{
		msh_free_setnull((void **)save);
		msh_free_setnull((void **)cmd);
		return (!MSH_CONTINUE);
	}
	free(*save);
	*save = new_save;
	return (!MSH_CONTINUE);
}
