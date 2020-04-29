/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:56 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:03 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void				update_life(t_player_items *p_i, int delta, int *pause)
{
	if (p_i->life_led == 1)
	{
		p_i->life -= (double)delta * 0.008f;
		if ((int)p_i->life <= 0)
			*pause = 1;
	}
}
