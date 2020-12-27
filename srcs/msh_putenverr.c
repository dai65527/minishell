/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_putenverr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 15:55:20 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/25 16:00:53 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			msh_putenverr(char *cmdname, char *envkey, int ret)
{
	ft_putstr_fd(MSH_NAME, FD_STDERR);
	ft_putstr_fd(": ", FD_STDERR);
	ft_putstr_fd(cmdname, FD_STDERR);
	ft_putstr_fd(": `", FD_STDERR);
	ft_putstr_fd(envkey, FD_STDERR);
	ft_putstr_fd("': not a valid identifier\n", FD_STDERR);
	return (ret);
}
