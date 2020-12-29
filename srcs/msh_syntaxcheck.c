/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_syntaxcheck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 08:44:34 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/29 09:25:11 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "minishell.h"

#define F_FIRST		1
#define F_ESCAPED	2

static ssize_t	check_flag(const char *save, size_t len, uint32_t *flg)
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

static ssize_t	check_quote(const char *save, size_t len, uint32_t *flg)
{
	size_t	begin;
	char	token[2];

	if ((save[len] != '\'' && save[len] != '"') || (*flg & F_ESCAPED))
		return (0);
	begin = len;
	token[1] = '\0';
	while (msh_isspace(save[++len]))
		;
	while (save[len] != save[begin])
	{
		if (save[len] == '\0' || save[len] == '\n')
		{
			token[0] = save[len];
			return (msh_put_syntaxerr(token));
		}
		len++;
	}
	*flg = 0;
	return (++len - begin);
}

static ssize_t	check_redirect(const char *save, size_t len, uint32_t *flg)
{
	size_t	begin;
	char	token[2];

	if ((save[len] != '<' && save[len] != '>') || (*flg & F_ESCAPED))
		return (0);
	token[1] = '\0';
	begin = len;
	if (!ft_strncmp(save + len, ">>", 2))
		len++;
	while (msh_isspace(save[++len]))
		;
	if (save[len] == '>' || save[len] == '<' || save[len] == '|'
			|| save[len] == '\0' || save[len] == '\n' || save[len] == ';')
	{
		token[0] = save[len];
		return (msh_put_syntaxerr(token));
	}
	*flg = 0;
	return (len - begin);
}

static ssize_t	check_pipe(const char *save, size_t len, uint32_t *flg)
{
	size_t	begin;
	char	token[2];

	if ((save[len] != '|') || (*flg & F_ESCAPED))
		return (0);
	token[1] = '\0';
	begin = len;
	if (*flg & F_FIRST)
		return (msh_put_syntaxerr("|"));
	while (msh_isspace(save[++len]))
		;
	if (save[len] == '>' || save[len] == '<' || save[len] == '|'
			|| save[len] == '\0' || save[len] == '\n' || save[len] == ';')
	{
		token[0] = save[len];
		return (msh_put_syntaxerr(token));
	}
	*flg = 0;
	return (len - begin);
}

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
		if (((ret = check_quote(save, len, &flg)) != 0)
			|| ((ret = check_redirect(save, len, &flg)) != 0)
			|| ((ret = check_pipe(save, len, &flg)) != 0))
		{
			if (ret < 0)
				return (-1);
		}
		else
			if (check_flag(save, len, &flg) != 0)
				return (-1);
		len = (ret == 0) ? (len + 1) : (len + ret);
	}
	return (1);
}
