/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_initsignal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 13:31:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/23 14:22:39 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

/*
**	Sub function: putprompt
**
**	Used in case ctrl + C (SIGINT) has pushed.
**	Delete "^C" and newline followed by new prompt.
*/

static void		putprompt(int sig)
{
	(void)sig;
	ft_putstr_fd("\b\b  \b\n", FD_STDERR);
	ft_putstr_fd(MSH_PROMPT, FD_STDERR);
}

/*
**	Sub function: donothing
**
**	Used in case ctrl + D (SIGQUIT) has pushed.
**	Delete "^\" and donothing.
*/

static void		donothing(int sig)
{
	(void)sig;
	ft_putstr_fd("\b\b  \b\b", FD_STDERR);
}

/*
**	Function: msh_initsignal
**
**	Initialize signal handler of minishell.
*/

int				msh_initsignal(void)
{
	if (signal(SIGINT, putprompt) == SIG_ERR)
		return (-1);
	if (signal(SIGQUIT, donothing) == SIG_ERR)
		return (-1);
	return (0);
}
