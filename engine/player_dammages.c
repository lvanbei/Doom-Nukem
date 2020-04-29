/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_dammages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:08 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:21 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int			check_monster_sector(t_engine *eng)
{
	int		i;

	i = -1;
	while (++i < (int)eng->num_things)
		if ((int)eng->player.sector == eng->things[i].sector
				&& eng->things[i].type == TH_MONSTER)
			return (1);
	return (0);
}

void		player_dammages(t_engine *eng, t_player_items *p_i)
{
	double	delta;
	int		i;

	delta = 0.65f;
	i = -1;
	if (check_monster_sector(eng))
		while (++i < (int)eng->num_things)
			if (eng->things[i].type == TH_MONSTER)
				if (eng->player.x - delta <= eng->things[i].x &&
						eng->player.x + delta >= eng->things[i].x &&
						eng->player.y - delta <= eng->things[i].y &&
						eng->player.y + delta >= eng->things[i].y &&
						eng->player.z <=
						eng->sectors[eng->player.sector].floor_height + 1.5f)
					p_i->life_led = 1;
}
