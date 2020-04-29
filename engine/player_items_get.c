/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_items_get.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:25 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:29 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int					find_item(t_engine *eng, double x_pos_item,
double y_pos_item, int item_num)
{
	t_player_items	*p_i;
	double			delta;

	delta = 1.0f;
	p_i = &eng->p_i;
	if (eng->player.x >= x_pos_item - delta &&
	eng->player.x <= x_pos_item + delta && eng->player.y >= y_pos_item - delta
	&& eng->player.y <= y_pos_item + delta &&
	eng->player.z <= eng->sectors[eng->player.sector].floor_height + 2.0f)
	{
		save_item_inv(p_i, eng->things[item_num].type);
		slow_memmove(&eng->things[item_num], &eng->things[item_num] + 1,
		sizeof(t_thing) * ((eng->num_things + eng->num_projectiles - 1)
		- item_num));
		eng->num_things--;
		return (1);
	}
	return (0);
}

int					check_things_sector(t_engine *eng)
{
	int i;

	i = -1;
	while (++i < (int)eng->num_things)
		if ((int)eng->player.sector == eng->things[i].sector &&
		(eng->things[i].type == TH_HEAL || eng->things[i].type == TH_AMMO
		|| eng->things[i].type == TH_KEY ||
		eng->things[i].type == TH_JETPACK_FUEL
		|| eng->things[i].type == TH_RPG))
			return (1);
	return (0);
}

void				player_items_get(t_engine *eng)
{
	int				i;
	t_player_items	*p_i;

	p_i = &eng->p_i;
	i = -1;
	if (p_i->item_led == 1 && eng->num_things > 0 &&
	check_things_sector(eng) == 1)
		while (++i < (int)eng->num_things)
			if ((eng->things[i].type == TH_HEAL ||
			eng->things[i].type == TH_AMMO ||
			eng->things[i].type == TH_KEY ||
			eng->things[i].type == TH_JETPACK_FUEL
			|| eng->things[i].type == TH_RPG)
			&& find_item(eng, eng->things[i].x,
			eng->things[i].y, i) == 1)
			{
				p_i->find_item_led = 1;
				break ;
			}
	p_i->item_led = 0;
}
