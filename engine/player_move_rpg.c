/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_rpg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:43 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:38 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void		move_rpg_3(t_player_items *p_i,
const uint8_t *key_states, double delta)
{
	if (p_i->ui_rect[UI_RECT_RPG_1].y < p_i->pos_rpg_y &&
	!key_states[SDL_SCANCODE_W])
	{
		p_i->var_height_rpg += delta / ((0.2 * 1000.0f) / DELTA_RPG_Y);
		p_i->ui_rect[UI_RECT_RPG_1].y = p_i->var_height_rpg;
		p_i->ui_rect[UI_RECT_RPG_2].y = p_i->var_height_rpg - 10;
		p_i->ui_rect[UI_RECT_RPG_3].y = p_i->var_height_rpg - 24;
	}
	if (key_states[SDL_SCANCODE_S] &&
	p_i->ui_rect[UI_RECT_RPG_1].y < p_i->pos_rpg_y + DELTA_RPG_Y)
	{
		p_i->var_height_rpg += delta / ((0.2 * 1000.0f) / DELTA_RPG_Y);
		p_i->ui_rect[UI_RECT_RPG_1].y = p_i->var_height_rpg;
		p_i->ui_rect[UI_RECT_RPG_2].y = p_i->var_height_rpg - 10;
		p_i->ui_rect[UI_RECT_RPG_3].y = p_i->var_height_rpg - 24;
	}
	if (p_i->ui_rect[UI_RECT_RPG_1].y > p_i->pos_rpg_y &&
	!key_states[SDL_SCANCODE_S])
	{
		p_i->var_height_rpg -= delta / ((0.2 * 1000.0f) / DELTA_RPG_Y);
		p_i->ui_rect[UI_RECT_RPG_1].y = p_i->var_height_rpg;
		p_i->ui_rect[UI_RECT_RPG_2].y = p_i->var_height_rpg - 10;
		p_i->ui_rect[UI_RECT_RPG_3].y = p_i->var_height_rpg - 24;
	}
}

static void		move_rpg_2(t_player_items *p_i,
const uint8_t *key_states, double delta)
{
	if (key_states[SDL_SCANCODE_D] &&
	p_i->ui_rect[UI_RECT_RPG_1].x < p_i->pos_rpg_x + DELTA_RPG_X)
	{
		p_i->var_width_rpg += delta / ((0.2 * 1000.0f) / DELTA_RPG_X);
		p_i->ui_rect[UI_RECT_RPG_1].x = p_i->var_width_rpg;
		p_i->ui_rect[UI_RECT_RPG_2].x = p_i->var_width_rpg + 88;
		p_i->ui_rect[UI_RECT_RPG_3].x = p_i->var_width_rpg + 72;
	}
	if (p_i->ui_rect[UI_RECT_RPG_1].x > p_i->pos_rpg_x &&
	!key_states[SDL_SCANCODE_D])
	{
		p_i->var_width_rpg -= delta / ((0.2 * 1000.0f) / DELTA_RPG_X);
		p_i->ui_rect[UI_RECT_RPG_1].x = p_i->var_width_rpg;
		p_i->ui_rect[UI_RECT_RPG_2].x = p_i->var_width_rpg + 88;
		p_i->ui_rect[UI_RECT_RPG_3].x = p_i->var_width_rpg + 72;
	}
	if (key_states[SDL_SCANCODE_W] &&
	p_i->ui_rect[UI_RECT_RPG_1].y > p_i->pos_rpg_y - DELTA_RPG_Y)
	{
		p_i->var_height_rpg -= delta / ((0.2 * 1000.0f) / DELTA_RPG_Y);
		p_i->ui_rect[UI_RECT_RPG_1].y = p_i->var_height_rpg;
		p_i->ui_rect[UI_RECT_RPG_2].y = p_i->var_height_rpg - 10;
		p_i->ui_rect[UI_RECT_RPG_3].y = p_i->var_height_rpg - 24;
	}
	move_rpg_3(p_i, key_states, delta);
}

void			move_rpg(t_player_items *p_i,
const uint8_t *key_states, double delta)
{
	if (!p_i->change_gun_led && p_i->gun_number == 1 &&
	!p_i->gun_load_led && !p_i->key_hand)
	{
		if (key_states[SDL_SCANCODE_A] &&
		p_i->ui_rect[UI_RECT_RPG_1].x > p_i->pos_rpg_x - DELTA_RPG_X)
		{
			p_i->var_width_rpg -= delta / ((0.2 * 1000.0f) / DELTA_RPG_X);
			p_i->ui_rect[UI_RECT_RPG_1].x = p_i->var_width_rpg;
			p_i->ui_rect[UI_RECT_RPG_2].x = p_i->var_width_rpg + 88;
			p_i->ui_rect[UI_RECT_RPG_3].x = p_i->var_width_rpg + 72;
		}
		if (p_i->ui_rect[UI_RECT_RPG_1].x < p_i->pos_rpg_x &&
		!key_states[SDL_SCANCODE_A])
		{
			p_i->var_width_rpg += delta / ((0.2 * 1000.0f) / DELTA_RPG_X);
			p_i->ui_rect[UI_RECT_RPG_1].x = p_i->var_width_rpg;
			p_i->ui_rect[UI_RECT_RPG_2].x = p_i->var_width_rpg + 88;
			p_i->ui_rect[UI_RECT_RPG_3].x = p_i->var_width_rpg + 72;
		}
		move_rpg_2(p_i, key_states, delta);
	}
}
