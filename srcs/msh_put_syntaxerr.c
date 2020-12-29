/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_put_syntaxerr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:03:51 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/29 09:10:00 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t			msh_put_syntaxerr(const char *token)
{
	ft_putstr_fd(MSH_NAME, FD_STDERR);
	ft_putstr_fd(": syntax error near unexpected token `", FD_STDERR);
	if (*token == '\n')
		ft_putstr_fd("newline", FD_STDERR);
	else if (*token == '\0')
		ft_putstr_fd("EOF", FD_STDERR);
	else if (*token == '>' || *token == '<' || *token == '|')
		ft_putchar_fd(*token, FD_STDERR);
	else
		ft_putstr_fd((char *)token, FD_STDERR);
	ft_putstr_fd("'\n", FD_STDERR);
	return (-1);
}
