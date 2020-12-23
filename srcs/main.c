/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:37:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/23 14:54:54 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include "minishell.h"

/*
**	function: main
**
**	- Entry and exit point of minishell.
**	- Do initialization, call mainloop and termination process of mshinfo.
*/

int		main(int argc, char **argv, char **envp)
{
	int			ret;
	t_mshinfo	mshinfo;

	if ((ret = msh_mshinfo_init(&mshinfo)) != 0)
		return (ret);
	if (!(mshinfo.envlst = msh_parse_envp(envp)))
		return (errno);
	if (argc <= 1)
		mshinfo.fd_cmdsrc = mshinfo.fd_std[0];
	else if ((mshinfo.fd_cmdsrc = open(argv[1], O_RDONLY)) < 0)
		return (msh_puterr("minishell", NULL, errno));
	ret = msh_loop(&mshinfo);
	msh_mshinfo_free(&mshinfo);
	return (ret);
}
