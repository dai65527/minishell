/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store_iflt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:48:02 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/11 15:52:13 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_store_iflt_mts(t_float *iflt)
{
	int			i;
	uint64_t	mts_bin;
	int8_t		mts[FLT_MTSSIZE];

	ft_bzero(iflt->mts_dec, sizeof(iflt->mts_dec));
	if (iflt->exp >= FLT_FRACBIT || (!iflt->frac && iflt->exp == -FLT_EXPBIAS))
		return ;
	if (iflt->exp >= 0)
		mts_bin = iflt->frac << iflt->exp;
	else if (iflt->exp == -FLT_EXPBIAS)
		mts_bin = iflt->frac;
	else
		mts_bin = (iflt->frac >> 1) | (1LL << (sizeof(mts_bin) * 8 - 1));
	ft_bzero(mts, sizeof(mts));
	mts[0] = 5;
	i = 0;
	while (i++ < -iflt->exp - 1)
		ft_mts_divbytwo(mts, FLT_MTSSIZE);
	i = -1;
	while (++i < (FLT_FRACBIT + 1))
	{
		if (mts_bin & (1LL << ((sizeof(mts_bin) * 8 - 1) - i)))
			ft_arr_add(iflt->mts_dec, mts, FLT_MTSSIZE);
		ft_mts_divbytwo(mts, FLT_MTSSIZE);
	}
}

static void		ft_store_iflt_int(t_float *iflt)
{
	int			i;
	int			offset;
	uint64_t	itg_bin;
	int8_t		itg[FLT_INTSIZE];

	ft_bzero(iflt->int_dec, sizeof(iflt->int_dec));
	if (iflt->exp <= 0)
	{
		if (!iflt->exp)
			iflt->int_dec[FLT_INTSIZE - 1] = 1;
		return ;
	}
	offset = (iflt->exp >= FLT_FRACBIT) ? FLT_FRACBIT : iflt->exp;
	itg_bin = (iflt->frac >> (sizeof(itg_bin) * 8 - offset)) | (1LL << offset);
	ft_bzero(itg, sizeof(itg));
	itg[FLT_INTSIZE - 1] = 1;
	i = -1;
	while (++i < (FLT_FRACBIT + 1))
	{
		if (itg_bin & (1LL << i))
			ft_arr_add(iflt->int_dec, itg, FLT_INTSIZE);
		ft_itg_dbl(itg, FLT_INTSIZE);
	}
	while (++i <= iflt->exp + 1)
		ft_itg_dbl(iflt->int_dec, FLT_INTSIZE);
}

t_float			ft_store_iflt(double num)
{
	uint64_t	mem;
	t_float		iflt;

	ft_memcpy(&mem, &num, sizeof(num));
	iflt.sign = mem >> (FLT_FRACBIT + FLT_EXPBIT);
	iflt.exp = (mem >> FLT_FRACBIT & ~(1 << FLT_EXPBIT)) - FLT_EXPBIAS;
	iflt.frac = mem << (FLT_EXPBIT + 1);
	ft_store_iflt_int(&iflt);
	ft_store_iflt_mts(&iflt);
	return (iflt);
}
