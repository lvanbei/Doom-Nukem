/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_save_items.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:19:08 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:19:09 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void			update_item_life(t_player_items *p_i, int item_type)
{
	if (item_type == TH_HEAL && p_i->life < 200)
	{
		if (p_i->life >= 180)
			p_i->life = 199;
		else
			p_i->life += 20;
	}
}

static void			update_item_ammo(t_player_items *p_i, int item_type)
{
	if ((item_type == TH_AMMO || (item_type == TH_RPG &&
	p_i->inv_items[UI_ITEM_RPG])) &&
	p_i->ammo_rpg < 200 && p_i->ammo_gun < 200)
	{
		if (p_i->gun_number == 0 && item_type != TH_RPG)
		{
			if (p_i->ammo_gun >= 180)
				p_i->ammo_gun = 199;
			else
			{
				p_i->ammo_gun += 20;
				p_i->ammo_per_load_gun = p_i->ammo_gun - 7;
			}
		}
		else
		{
			if (p_i->ammo_rpg >= 195)
				p_i->ammo_rpg = 199;
			else
				p_i->ammo_rpg += 5;
		}
	}
}

static void			update_item_jp(t_player_items *p_i, int item_type)
{
	if (item_type == TH_JETPACK_FUEL &&
	p_i->inv_items[UI_ITEM_JET_PACK] == 1 && p_i->percent_jp >= 0)
	{
		if (p_i->percent_jp <= 149)
			p_i->percent_jp += 50;
		else
			p_i->percent_jp = 199;
	}
	if (item_type == TH_JETPACK_FUEL && p_i->inv_items[UI_ITEM_JET_PACK] == 0)
	{
		p_i->inv_items[UI_ITEM_JET_PACK] = 1;
		if (p_i->percent_jp != 100.0f)
			p_i->percent_jp = 50;
	}
}

void				save_item_inv(t_player_items *p_i, int item_type)
{
	update_item_life(p_i, item_type);
	update_item_ammo(p_i, item_type);
	update_item_jp(p_i, item_type);
	if (item_type == TH_KEY)
		p_i->inv_items[UI_ITEM_KEY] = 1;
	if (item_type == TH_RPG)
		p_i->inv_items[UI_ITEM_RPG] = 1;
}
