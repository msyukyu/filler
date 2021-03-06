/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_decoder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:05:14 by dabeloos          #+#    #+#             */
/*   Updated: 2019/04/17 12:05:27 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

unsigned char			ydecode_player(t_in in, t_ply *me, t_ply *en)
{
	while (in.s[in.p] != '\0' && in.s[in.p] != 'p')
		in.p++;
	if (in.s[in.p++] != 'p')
		return (0);
	if (in.s[in.p] == '1')
	{
		me->o = 'O';
		en->o = 'X';
	}
	else if (in.s[in.p] == '2')
	{
		me->o = 'X';
		en->o = 'O';
	}
	else
		return (0);
	return (1);
}
