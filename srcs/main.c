/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:37:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/24 18:23:58 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	t_mshinfo	mshinfo;

	msh_init_mshinfo(&mshinfo);
	if (!(mshinfo.envlst = msh_parse_envp(envp)))
		return (msh_exit_by_err());
	if (argc <= 1)
		mshinfo.fd_cmdsrc = FD_STDIN;
	else if ((mshinfo.fd_cmdsrc = open(argv[1], O_RDONLY)) < 0)
		return (msh_exit_by_err());
	return (msh_loop(&mshinfo));
}
