/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_gun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:40 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:36 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void		move_gun_3(t_player_items *p_i,
const uint8_t *key_states, int d)
{
	if (p_i->ui_rect[UI_RECT_GUN].y < p_i->pos_gun_y &&
			!key_states[SDL_SCANCODE_W])
	{
		p_i->var_height_gun += d / ((0.2 * 1000.0f) / DELTA_GUN_Y);
		p_i->ui_rect[UI_RECT_GUN].y = p_i->var_height_gun;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_1].y = p_i->var_height_gun - 31;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_2].y = p_i->var_height_gun - 12;
	}
	if (key_states[SDL_SCANCODE_S] &&
			p_i->ui_rect[UI_RECT_GUN].y < p_i->pos_gun_y + DELTA_GUN_Y)
	{
		p_i->var_height_gun += d / ((0.2 * 1000.0f) / DELTA_GUN_Y);
		p_i->ui_rect[UI_RECT_GUN].y = p_i->var_height_gun;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_1].y = p_i->var_height_gun - 31;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_2].y = p_i->var_height_gun - 12;
	}
	if (p_i->ui_rect[UI_RECT_GUN].y > p_i->pos_gun_y &&
	!key_states[SDL_SCANCODE_S])
	{
		p_i->var_height_gun -= d / ((0.2 * 1000.0f) / DELTA_GUN_Y);
		p_i->ui_rect[UI_RECT_GUN].y = p_i->var_height_gun;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_1].y = p_i->var_height_gun - 31;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_2].y = p_i->var_height_gun - 12;
	}
}

static void		move_gun_2(t_player_items *p_i,
const uint8_t *key_states, int delta)
{
	if (key_states[SDL_SCANCODE_D] &&
	p_i->ui_rect[UI_RECT_GUN].x < p_i->pos_gun_x + DELTA_GUN_X)
	{
		p_i->var_width_gun += delta / ((0.2 * 1000.0f) / DELTA_GUN_X);
		p_i->ui_rect[UI_RECT_GUN].x = p_i->var_width_gun;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_1].x = p_i->var_width_gun;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_2].x = p_i->var_width_gun;
	}
	if (p_i->ui_rect[UI_RECT_GUN].x > p_i->pos_gun_x &&
	!key_states[SDL_SCANCODE_D])
	{
		p_i->var_width_gun -= delta / ((0.2 * 1000.0f) / DELTA_GUN_X);
		p_i->ui_rect[UI_RECT_GUN].x = p_i->var_width_gun;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_1].x = p_i->var_width_gun;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_2].x = p_i->var_width_gun;
	}
	if (key_states[SDL_SCANCODE_W] &&
	p_i->ui_rect[UI_RECT_GUN].y > p_i->pos_gun_y - DELTA_GUN_Y)
	{
		p_i->var_height_gun -= delta / ((0.2 * 1000.0f) / DELTA_GUN_Y);
		p_i->ui_rect[UI_RECT_GUN].y = p_i->var_height_gun;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_1].y = p_i->var_height_gun - 31;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_2].y = p_i->var_height_gun - 12;
	}
	move_gun_3(p_i, key_states, delta);
}

void			move_gun(t_player_items *p_i,
const uint8_t *key_states, double delta)
{
	if (p_i->change_gun_led == 0 && p_i->gun_number == 0
	&& p_i->gun_load_led == 0 && p_i->key_hand == 0)
	{
		if (key_states[SDL_SCANCODE_A] &&
		p_i->ui_rect[UI_RECT_GUN].x > p_i->pos_gun_x - DELTA_GUN_X)
		{
			p_i->var_width_gun -= delta / ((0.2 * 1000.0f) / DELTA_GUN_X);
			p_i->ui_rect[UI_RECT_GUN].x = p_i->var_width_gun;
			p_i->ui_rect[UI_RECT_GUN_SHOOT_1].x = p_i->var_width_gun;
			p_i->ui_rect[UI_RECT_GUN_SHOOT_2].x = p_i->var_width_gun;
		}
		if (p_i->ui_rect[UI_RECT_GUN].x < p_i->pos_gun_x &&
		!key_states[SDL_SCANCODE_A])
		{
			p_i->var_width_gun += delta / ((0.2 * 1000.0f) / DELTA_GUN_X);
			p_i->ui_rect[UI_RECT_GUN].x = p_i->var_width_gun;
			p_i->ui_rect[UI_RECT_GUN_SHOOT_1].x = p_i->var_width_gun;
			p_i->ui_rect[UI_RECT_GUN_SHOOT_2].x = p_i->var_width_gun;
		}
		move_gun_2(p_i, key_states, delta);
	}
}
