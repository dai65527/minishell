/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_putwelcome.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:57:59 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/24 11:18:15 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put(const char *str)
{
	ft_putstr_fd((char *)str, FD_STDERR);
}

void		msh_putwelcome(void)
{
	put("              _       _      __         ____   ____ \n");
	put("   ____ ___  (_)___  (_)____/ /_  ___  / / /  / __ \\\n");
	put("  / __ `__ \\/ / __ \\/ / ___/ __ \\/ _ \\/ / /  / / / /\n");
	put(" / / / / / / / / / / (__  ) / / /  __/ / /  / /_/ / \n");
	put("/_/ /_/ /_/_/_/ /_/_/____/_/ /_/\\___/_/_/  /_____/  \n");
	put("                               by Dhasegaw & Dnakano\n");
	put("                                                    \n");
	put("              ____----------- _____\n");
	put("\\~~~~~~~~~~/~_--~~~------~~~~~     \\\n");
	put(" `---`\\  _-~      |                   \\\n");
	put("   _-~  <_         |                     \\[]\n");
	put(" / ___     ~~--[\"\"] |      ________-------'_\n");
	put("> /~` \\    |-.   `\\~~.~~~~~                _ ~ - _\n");
	put(" ~|  ||\\%  |       |    ~  ._                ~ _   ~ ._\n");
	put("   `_//|_%  \\      |          ~  .              ~-_   /\\\n");
	put("          `--__     |    _-____  /\\               ~-_ \\/.\n");
	put("               ~--_ /  ,/ -~-_ \\ \\/       __________---~/\n");
	put("                  ~~-/._<   \\ \\`~~~~~~~   |_42_|  ##--~/\n");
	put("                         \\    ) |`------##---~~~~-~  ) )\n");
	put("                          ~-_/_/                  ~~ ~~\n");
}