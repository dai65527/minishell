/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_uint128.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:09:44 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/30 17:15:57 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atof.h"

t_uint128	uint128_leftshift(t_uint128 n, unsigned int width)
{
	t_uint128	res;

	if (width >= 128)
		uint128_bzero(&res);
	else if (width >= 64)
	{
		res.lsb = 0;
		res.msb = n.lsb << (width - 64);
	}
	else
	{
		res.lsb = n.lsb << width;
		res.msb = (n.msb << width) | (n.lsb >> (64 - width));
	}
	return (res);
}

t_uint128	uint128_rightshift(t_uint128 n, unsigned int width)
{
	t_uint128	res;

	if (width >= 128)
		uint128_bzero(&res);
	else if (width >= 64)
	{
		res.msb = 0;
		res.lsb = n.msb >> (width - 64);
	}
	else
	{
		res.msb = n.msb >> width;
		res.lsb = (n.lsb >> width) | (n.msb << (64 - width));
	}
	return (res);
}

t_uint128	uint128_sum(t_uint128 a, t_uint128 b)
{
	t_uint128	res;
	uint64_t	tmp;

	res.lsb = a.lsb + b.lsb;
	res.msb = a.msb + b.msb;
	tmp = (a.lsb >> 1) + (b.lsb >> 1);
	if ((a.lsb & 1) && (b.lsb & 1))
		tmp++;
	if (tmp | (1ULL << 63))
		res.msb++;
	return (res);
}

t_uint128	uint128_tenx(t_uint128 n)
{
	t_uint128	res;

	res = uint128_sum(uint128_leftshift(n, 1), uint128_leftshift(n, 3));
	return (res);
}

t_uint128	uint128_tendiv(t_uint128 n)
{
	t_uint128	res;
	uint64_t	tmp;
	uint64_t	res_lsblsb;
	uint64_t	res_lsbmsb;

	res.msb = n.msb / 10;
	tmp = ((n.msb % 10) << 32) | (n.lsb >> 32);
	res_lsbmsb = tmp / 10;
	res_lsblsb = ((tmp % 10) << 32) | (n.lsb & 0xFFFFFFFF) / 10;
	res.lsb = (res_lsbmsb << 32) | res_lsblsb;
	return (res);
}
