/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signalhandler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 13:31:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/29 17:16:26 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

/*
**	Function: msh_sighandle_putendl
**
**	Used in case ctrl + C (SIGINT) has pushed.
**	Delete "^C" and newline.
*/

void		msh_sighandle_putendl(int sig)
{
	(void)sig;
	ft_putstr_fd("\b\b  \b\n", FD_STDERR);
}

/*
**	Function: msh_sighandle_putprompt
**
**	Used in case ctrl + C (SIGINT) has pushed.
**	Delete "^C" and newline followed by new prompt.
*/

void		msh_sighandle_putprompt(int sig)
{
	(void)sig;
	g_flg_termed = 1;
	ft_putstr_fd("\b\b  \b\n", FD_STDERR);
	ft_putstr_fd(MSH_PROMPT, FD_STDERR);
}

/*
**	Function: msh_sighandle_donothing
**
**	Used in case ctrl + \ (SIGQUIT) has pushed.
**	Delete "^\" and donothing.
*/

void		msh_sighandle_donothing(int sig)
{
	(void)sig;
	g_flg_termed = 1;
	ft_putstr_fd("\b\b  \b\b", FD_STDERR);
}

/*
**	Function: msh_sighandle_putquit
**
**	Used in case ctrl + \ (SIGQUIT) has pushed.
**	Put "Quit: 3" and new line.
*/

void		msh_sighandle_putquit(int sig)
{
	ft_putstr_fd("Quit: ", FD_STDERR);
	ft_putnbr_fd(sig, FD_STDERR);
	ft_putstr_fd("\n", FD_STDERR);
}

/*
**	Function: msh_initsignal
**
**	Initialize signal handler of minishell.
*/

int			msh_initsignal(void)
{
	g_flg_termed = 0;
	if (signal(SIGINT, msh_sighandle_putprompt) == SIG_ERR)
		return (msh_puterr(MSH_NAME, NULL, -1));
	if (signal(SIGQUIT, msh_sighandle_donothing) == SIG_ERR)
		return (msh_puterr(MSH_NAME, NULL, -1));
	return (0);
}
