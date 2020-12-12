/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_argv_redirect_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:18:04 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/12 02:22:17 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

size_t	msh_hundle_redirect_pipe(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	size_t	begin;

	begin = len;
	if (!ft_strncmp(&save[len], ">>", 2))
	{		
		ft_putendl_fd(">>", 1);
		len += 2;
		// len += hundle_append(mshinfo, &save[len], len);
	}
	else if (save[len] == '>')
	{
		ft_putendl_fd(">", 1);
		len++;
		// len += hundle_write(mshinfo, &save[len], len);
	}
	else if (save[len] == '<')
	{
		ft_putendl_fd("<", 1);
		len++;
		// len += hundle_read(mshinfo, &save[len], len);
	}
	else if (save[len] == '|')
	{
		ft_putendl_fd("|", 1);
		len++;
		// len += hundle_pipe(mshinfo, &save[len], len);
	}
	return (len - begin);
}

size_t	msh_hundle_redirect_fd(t_mshinfo *mshinfo, char *save, size_t len)
{
	size_t	begin;

	begin = len;
	while (ft_isdigit(save[len]))
		len++;
	if (!save[len] || (save[len] && !ft_strchr("<>", save[len])))
		return (0);
	if (!ft_strncmp(&save[len], ">>", 2))
	{
		write(1, &save[begin], len - begin);		
		ft_putendl_fd(">>", 1);
		len += 2;
		// len += hundle_append(mshinfo, &save[len], len);
	}
	else if (save[len] == '>')
	{
		write(1, &save[begin], len - begin);
		ft_putendl_fd(">", 1);
		len++;
		// len += hundle_write(mshinfo, &save[len], len);
	}
	else if (save[len] == '<')
	{
		write(1, &save[begin], len - begin);
		ft_putendl_fd("<", 1);
		len++;
		// len += hundle_read(mshinfo, &save[len], len);
	}
	while (save[len] && msh_is_space(save[len]))
		len++;
	return (len - begin);
}
