/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:37:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/21 17:23:46 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
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

	msh_mshinfo_init(&mshinfo);
	if (!(mshinfo.envlst = msh_parse_envp(envp)))
		return (errno);
	if (argc <= 1)
		mshinfo.fd_cmdsrc = FD_STDIN;
	else if ((mshinfo.fd_cmdsrc = open(argv[1], O_RDONLY)) < 0)
		return (msh_puterr("minishell", NULL, errno));
	ret = msh_loop(&mshinfo);
	msh_mshinfo_free(&mshinfo);
	return (ret);
}
