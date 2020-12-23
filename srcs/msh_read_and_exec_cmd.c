/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_read_and_exec_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:02:21 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/23 11:57:51 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "minishell.h"

#define MSH_READBUFLEN ARG_MAX

/*
**	Sub function: free_buf_return
**
**	Free save and buf and return ret.
*/

int			free_buf_return(char *buf, char *save, int ret)
{
	if (buf)
		msh_free_setnull((void *)&buf);
	free(save);
	return (ret);
}

/*
**	Sub function: joinbuf
**
**	Connect buf to save.
**	Returns 0 when succeed or non zero when failure.
*/

static int	joinbuf(char **save, char *buf, ssize_t len)
{
	ssize_t		save_len;
	char		*save_new;

	save_len = ft_strlen(*save);
	if (!(save_new = (char *)malloc(sizeof(char) * (save_len + len + 1))))
		return (msh_puterr("minishell", NULL, errno));
	ft_strlcpy(save_new, *save, save_len + 1);
	ft_strlcat(save_new, buf, len + save_len + 1);
	free(*save);
	*save = save_new;
	return (0);
}

/*
**	Function: msh_read_and_exec_cmd.
**
**	Read from command source and save to "save".
**	Pass save to msh_paerse_and_exec_cmd.
*/

int			msh_read_and_exec_cmd(t_mshinfo *mshinfo)
{
	ssize_t		ret;
	char		*buf;
	char		*save;

	if (!(save = ft_strdup("")))
		return (msh_puterr(MSH_NAME, NULL, -1));
	if (!(buf = (char *)malloc(sizeof(char) * MSH_READBUFLEN)))
		return (free_buf_return(NULL, save, msh_puterr(MSH_NAME, NULL, -1)));
	mshinfo->n_proc = 0;
	while ((ret = read(mshinfo->fd_std[0], buf, MSH_READBUFLEN)) >= 0)
	{
		if (ret == 0 && ft_strlen(save) == 0)
			return (free_buf_return(buf, save, 1));
		if (joinbuf(&save, buf, ret) < 0)
			return (free_buf_return(buf, save, -1));
		if ((ret = msh_syntaxcheck(save)) < 0)
			return (free_buf_return(buf, save, 0));
		else if (ret == 0)
			continue ;
		if (msh_parse_and_exec_cmd(mshinfo, &save) != 0)
			return (free_buf_return(buf, save, 0));
	}
	return (free_buf_return(buf, save, msh_puterr(MSH_NAME, NULL, -1)));
}
