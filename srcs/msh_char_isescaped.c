/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_char_isescaped.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 11:54:12 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/28 18:14:01 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** '\'によりエスケープされているかを判定する関数。
**
** 引数：
** s: ある文字列中の、エスケープされているか判定したい文字
** len_from_start: sが元の文字列のlen_from_start分の位置にある。
**
** 解説：
** sの直前に'\'が何個あるかで、エスケープされているかがわかる。
** 	奇数個： エスケープされている。
** 	偶数個： エスケープされていない（直前の'\'自体がエスケープされている）
*/

int			msh_isescaped(char *s, size_t len_from_start)
{
	int		i;
	int		flg_isescaped;

	flg_isescaped = 0;
	i = 1;
	while (i <= len_from_start && *(s - i) == '\\')
	{
		flg_isescaped = !flg_isescaped;
		i++;
	}
	return (flg_isescaped);
}
