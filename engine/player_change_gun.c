/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_change_gun.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:01 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:17 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void			gun_down(t_engine *eng)
{
	t_player_items	*p_i;

	p_i = &eng->p_i;
	if (p_i->ui_rect[UI_RECT_GUN].y < WIN_HEIGHT && p_i->gun_down == 0)
	{
		p_i->ui_rect[UI_RECT_GUN].y = p_i->var_height_gun_plus;
		SDL_BlitSurface(p_i->ui_surface[UI_GUN], NULL, eng->surface,
				&p_i->ui_rect[UI_RECT_GUN]);
	}
	else if (p_i->gun_down == 0 && p_i->ui_rect[UI_RECT_GUN].y >= WIN_HEIGHT)
	{
		p_i->gun_down = 1;
		p_i->ui_rect[UI_RECT_RPG_1].y = WIN_HEIGHT;
		p_i->var_height_rpg_min = WIN_HEIGHT;
	}
}

static void			rpg_up(t_engine *eng)
{
	t_player_items	*p_i;

	p_i = &eng->p_i;
	if (p_i->ui_rect[UI_RECT_RPG_1].y > WIN_HEIGHT -
			p_i->ui_surface[UI_RPG_1]->h + 10)
	{
		p_i->ui_rect[UI_RECT_RPG_1].y = p_i->var_height_rpg_min;
		SDL_BlitSurface(eng->p_i.ui_surface[UI_RPG_1], NULL,
				eng->surface, &p_i->ui_rect[UI_RECT_RPG_1]);
	}
	if (p_i->ui_rect[UI_RECT_RPG_1].y <= WIN_HEIGHT -
			p_i->ui_surface[UI_RPG_1]->h + 10)
	{
		p_i->ui_rect[UI_RECT_RPG_1].y = WIN_HEIGHT -
			p_i->ui_surface[UI_RPG_1]->h + 10;
		p_i->var_height_rpg_plus = WIN_HEIGHT - 97.0f + 10.0f;
		p_i->ui_rect[UI_RECT_RPG_2].y = 583;
		p_i->ui_rect[UI_RECT_RPG_3].y = 569;
		p_i->gun_number = 1;
		p_i->change_gun_led = 0;
		p_i->gun_down = 0;
		p_i->shoot_led = 0;
	}
}

static void			rpg_down(t_engine *eng)
{
	t_player_items	*p_i;

	p_i = &eng->p_i;
	if (p_i->ui_rect[UI_RECT_RPG_1].y <= WIN_HEIGHT && p_i->gun_down == 0)
	{
		p_i->ui_rect[UI_RECT_RPG_1].y = p_i->var_height_rpg_plus;
		SDL_BlitSurface(eng->p_i.ui_surface[UI_RPG_1], NULL,
				eng->surface, &p_i->ui_rect[UI_RECT_RPG_1]);
	}
	else if (p_i->gun_down == 0)
	{
		p_i->gun_down = 1;
		p_i->ui_rect[UI_RECT_GUN].y = WIN_HEIGHT;
		p_i->var_height_gun_min = WIN_HEIGHT;
	}
}

static void			gun_up(t_engine *eng)
{
	t_player_items	*p_i;

	p_i = &eng->p_i;
	if (p_i->ui_rect[UI_RECT_GUN].y >= WIN_HEIGHT -
			p_i->ui_surface[UI_GUN]->h + 20)
	{
		p_i->ui_rect[UI_RECT_GUN].y = p_i->var_height_gun_min;
		SDL_BlitSurface(p_i->ui_surface[UI_GUN], NULL, eng->surface,
				&p_i->ui_rect[UI_RECT_GUN]);
	}
	else
	{
		p_i->ui_rect[UI_RECT_GUN].y = WIN_HEIGHT -
			p_i->ui_surface[UI_GUN] ->h + 20;
		p_i->var_height_gun_plus = WIN_HEIGHT - 133.0f + 20.0f;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_1].y = WIN_HEIGHT -
			p_i->ui_surface[UI_GUN_SHOOT_1]->h + 20;
		p_i->ui_rect[UI_RECT_GUN_SHOOT_2].y = WIN_HEIGHT -
			p_i->ui_surface[UI_GUN_SHOOT_2]->h + 20;
		p_i->change_gun_led = 0;
		p_i->gun_number = 0;
		p_i->gun_down = 0;
	}
}

void				change_gun(t_engine *eng, t_player_items *p_i, int delta)
{
	if (p_i->change_gun_led && p_i->key_on == 0 && p_i->inv_items[UI_ITEM_RPG])
	{
		if (p_i->gun_down == 0 && p_i->gun_number == 0)
			p_i->var_height_gun_plus += (double)delta / p_i->timer_gun;
		if (p_i->gun_down == 1 && p_i->gun_number == 0)
			p_i->var_height_rpg_min -= (double)delta / p_i->timer_rpg;
		if (p_i->gun_down == 1 && p_i->gun_number == 1)
			p_i->var_height_gun_min -= (double)delta / p_i->timer_gun;
		if (p_i->gun_down == 0 && p_i->gun_number == 1)
			p_i->var_height_rpg_plus += (double)delta / p_i->timer_rpg;
		if (p_i->gun_number == 0)
		{
			gun_down(eng);
			if (p_i->gun_down == 1)
				rpg_up(eng);
		}
		if (p_i->gun_number == 1 && p_i->change_gun_led == 1)
		{
			rpg_down(eng);
			if (p_i->gun_down == 1)
				gun_up(eng);
		}
	}
	else
		eng->p_i.change_gun_led = 0;
}
