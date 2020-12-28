/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:36:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/24 21:30:13 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "minishell.h"

#define MSH_EXIT_NOERR 0
#define MSH_EXIT_ERR_TMARG 1
#define MSH_EXIT_ERR_NAN -1

static int		exit_arg_isnumeric(char *arg)
{
	if (!ft_isdigit(*arg) && *arg != '+' && *arg != '-')
		return (0);
	while (*(++arg))
	{
		if (!ft_isdigit(*arg))
			return (0);
	}
	return (1);
}

static void		msh_exit_puterr(char **argv, int errcode)
{
	char	buf[256];

	if (!errcode)
		return ;
	ft_strlcpy(buf, MSH_NAME, sizeof(buf));
	ft_strlcat(buf, ": exit : ", sizeof(buf));
	if (errcode == MSH_EXIT_ERR_NAN && argv[1])
	{
		ft_strlcat(buf, argv[1], sizeof(buf));
		ft_strlcat(buf, ": numeric argument required\n", sizeof(buf));
	}
	else if (errcode == MSH_EXIT_ERR_TMARG)
		ft_strlcat(buf, "too many arguments\n", sizeof(buf));
	else
		ft_strlcat(buf, "unknown error\n", sizeof(buf));
	ft_putstr_fd(buf, FD_STDERR);
}

static int		exit_get_returnval(char **argv, int *errcode)
{
	if (!argv[1])
		return (0);
	else if (!exit_arg_isnumeric(argv[1]))
	{
		*errcode = MSH_EXIT_ERR_NAN;
		return (-1);
	}
	else if (argv[2])
	{
		*errcode = MSH_EXIT_ERR_TMARG;
		return (1);
	}
	return (ft_atoi(argv[1]));
}

int				msh_exit(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	int		ret;
	int		errcode;

	errcode = 0;
	ret = exit_get_returnval(argv, &errcode);
	if (mshinfo->has_pipe || errcode == MSH_EXIT_ERR_TMARG)
	{
		if (errcode)
			msh_exit_puterr(argv, errcode);
		mshinfo->ret_last_cmd = (unsigned char)ret;
		return (0);
	}
	if (!flg_forked)
		ft_putstr_fd("exit\n", FD_STDERR);
	if (errcode)
		msh_exit_puterr(argv, errcode);
	msh_mshinfo_free(mshinfo);
	exit((unsigned char)ret);
}
