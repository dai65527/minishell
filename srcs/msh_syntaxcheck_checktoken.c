/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_syntaxcheck_checktoken.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 10:39:07 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/30 14:44:38 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "minishell.h"

#define F_FIRST		1
#define F_ESCAPED	2

ssize_t	msh_syntaxcheck_flag(const char *save, size_t len, uint32_t *flg)
{
	if (save[len] == '\\')
		*flg = (*flg & F_ESCAPED) ? 0 : F_ESCAPED;
	else if (save[len] == ';' && !(*flg & F_ESCAPED))
	{
		if (*flg & F_FIRST)
		{
			if ((len > 0 && save[len - 1] == ';') || save[len + 1] == ';')
				return (msh_put_syntaxerr(";;"));
			else
				return (msh_put_syntaxerr(";"));
		}
		*flg = F_FIRST;
	}
	else if (save[len] == '\n')
	{
		if (*flg & F_ESCAPED)
			return (msh_put_syntaxerr("\n"));
		*flg = F_FIRST;
	}
	else
		*flg = 0;
	return (0);
}

ssize_t	msh_syntaxcheck_quote(const char *save, size_t len, uint32_t *flg)
{
	size_t	begin;

	if ((save[len] != '\'' && save[len] != '"') || (*flg & F_ESCAPED))
		return (0);
	begin = len;
	while (msh_isspace(save[++len]))
		;
	while (save[len] != save[begin] || (*flg & F_ESCAPED && save[begin] == '"'))
	{
		if (save[len] == '\0' || save[len] == '\n')
			return (msh_put_syntaxerr(save + len));
		else if (save[len] == '\\')
			*flg = (*flg & F_ESCAPED) ? 0 : F_ESCAPED;
		else
			*flg = 0;
		len++;
	}
	*flg = 0;
	return (++len - begin);
}

ssize_t	msh_syntaxcheck_redirect(const char *save, size_t len, uint32_t *flg)
{
	size_t	begin;

	if ((save[len] != '<' && save[len] != '>') || (*flg & F_ESCAPED))
		return (0);
	begin = len;
	if (!ft_strncmp(save + len, ">>", 2))
		len++;
	while (msh_isspace(save[++len]))
		;
	if (save[len] == '>' || save[len] == '<' || save[len] == '|'
			|| save[len] == '\0' || save[len] == '\n' || save[len] == ';')
		return (msh_put_syntaxerr(save + len));
	*flg = 0;
	return (len - begin);
}

ssize_t	msh_syntaxcheck_pipe(const char *save, size_t len, uint32_t *flg)
{
	size_t	begin;

	if ((save[len] != '|') || (*flg & F_ESCAPED))
		return (0);
	begin = len;
	if (*flg & F_FIRST)
		return (msh_put_syntaxerr("|"));
	while (msh_isspace(save[++len]))
		;
	if (save[len] == '>' || save[len] == '<' || save[len] == '|'
			|| save[len] == '\0' || save[len] == '\n' || save[len] == ';')
		return (msh_put_syntaxerr(save + len));
	*flg = 0;
	return (len - begin);
}
