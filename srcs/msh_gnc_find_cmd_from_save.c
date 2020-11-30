/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_gnc_find_cmd_from_save.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:44:56 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/30 09:56:40 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

static size_t	gnc_cmdlen(char *save, int *flg_continue)
{
	size_t	len;

	len = 0;
	while (save[len] != '\n')
	{
		if (save[len] == '\0')
		{
			*flg_continue = 1;
			break ;
		}
		if (save[len] == ';')
		{
			if (!msh_isescaped(save + len, len))
				break ;
			ft_memmove(save + len - 1, save + len, ft_strlen(save + len) + 1);
			continue ;
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
