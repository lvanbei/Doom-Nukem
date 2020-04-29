/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:17 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:27 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void			init_var_menu(t_menu *menu)
{
	menu->which_menu = 0;
	menu->x = -20;
	menu->y = 128;
	menu->go_game = 0;
	menu->ret = -1;
	menu->timer_plus = -340.0f;
	menu->timer_min = 680.0f;
}

void			init_player_items_var_2(t_player_items *p_i)
{
	p_i->var_height_gun_plus = WIN_HEIGHT - 133.0f + 20.0f;
	p_i->var_height_gun_min = WIN_HEIGHT;
	p_i->var_height_rpg_plus = WIN_HEIGHT - 97.0f + 10.0f;
	p_i->var_height_rpg_min = WIN_HEIGHT;
	p_i->var_width_rpg = WIN_WIDTH - p_i->ui_surface[UI_RPG_1]->w + 20;
	p_i->var_height_rpg = WIN_WIDTH - p_i->ui_surface[UI_RPG_1]->h + 10;
	p_i->var_width_gun = WIN_WIDTH / 2 - p_i->ui_surface[UI_GUN]->w / 2 + 40;
	p_i->var_height_gun = WIN_HEIGHT - p_i->ui_surface[UI_GUN]->h + 20;
	p_i->timer_gun = ((CHANGEGUNTIMER * 1000.0f) / 123.0f) / 2.0f;
	p_i->timer_rpg = ((CHANGEGUNTIMER * 1000.0f) / 77.0f) / 2.0f;
	p_i->ammo_per_load_gun = p_i->ammo_gun - 7;
	p_i->pos_gun_x = WIN_WIDTH / 2 - p_i->ui_surface[UI_GUN]->w / 2 + 40;
	p_i->pos_gun_y = WIN_HEIGHT - p_i->ui_surface[UI_GUN]->h + 20;
	p_i->pos_rpg_x = WIN_WIDTH - p_i->ui_surface[UI_RPG_1]->w + 20;
	p_i->pos_rpg_y = WIN_HEIGHT - p_i->ui_surface[UI_RPG_1]->h + 10;
	p_i->key_hand = 0;
	p_i->activate_doors = 1;
}

void			init_player_items_var(t_player_items *p_i)
{
	p_i->inv_items[UI_ITEM_JET_PACK] = 0;
	p_i->inv_items[UI_ITEM_KEY] = 0;
	p_i->inv_items[UI_ITEM_RPG] = 0;
	p_i->delta_min = 0.0f;
	p_i->change_gun_led = 0;
	p_i->gun_number = 0;
	p_i->ammo_gun = 50;
	p_i->ammo_rpg = 10;
	p_i->gun_load_led = 0;
	p_i->life = 100;
	p_i->life_led = 0;
	p_i->shoot_led = 0;
	p_i->find_item_led = 0;
	p_i->gun_down = 0;
	p_i->rpg_shoot_led = 0;
	p_i->percent_jp = 100.0f;
	p_i->jet_pack_led = 0;
	p_i->item_led = 0;
	init_player_items_var_2(p_i);
}
