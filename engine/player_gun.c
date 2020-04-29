/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:15 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:25 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void			gun_reload_2(t_player_items *p_i, int *timer)
{
	if (*timer >= 250)
	{
		*timer = -300;
		p_i->gun_load_led = 0;
		p_i->ammo_per_load_gun -= 7 - (p_i->ammo_gun - p_i->ammo_per_load_gun);
	}
}

static void			gun_reload(t_engine *eng, t_player_items *p_i, int delta)
{
	static int		timer = -300;

	if ((p_i->gun_load_led || p_i->ammo_per_load_gun == p_i->ammo_gun)
	&& !p_i->shoot_led)
	{
		if (timer <= -150)
			SDL_BlitSurface(p_i->ui_surface[UI_GUN_LOAD_1]
			, NULL, eng->surface, &p_i->ui_rect[UI_RECT_GUN_LOAD_1]);
		if (timer > -150 && timer <= -75)
			SDL_BlitSurface(p_i->ui_surface[UI_GUN_LOAD_2]
			, NULL, eng->surface, &p_i->ui_rect[UI_RECT_GUN_LOAD_2]);
		if (timer > 75 && timer <= 250)
			SDL_BlitSurface(p_i->ui_surface[UI_GUN_LOAD_5],
			NULL, eng->surface, &p_i->ui_rect[UI_RECT_GUN_LOAD_5]);
		if (timer > -75 && timer <= 250)
			SDL_BlitSurface(p_i->ui_surface[UI_GUN_LOAD_2_BIS],
			NULL, eng->surface, &p_i->ui_rect[UI_RECT_GUN_LOAD_2_BIS]);
		if (timer > 0 && timer <= 75)
			SDL_BlitSurface(p_i->ui_surface[UI_GUN_LOAD_3],
			NULL, eng->surface, &p_i->ui_rect[UI_RECT_GUN_LOAD_3]);
		timer += delta / 1.5;
		gun_reload_2(p_i, &timer);
	}
}

static void			gun_shoot(t_engine *eng, t_player_items *p_i,
int delta, int *timer)
{
	if (p_i->shoot_led == 1 && p_i->ammo_gun >= 0)
	{
		if (*timer <= 0)
			SDL_BlitSurface(p_i->ui_surface[UI_GUN_SHOOT_2],
			NULL, eng->surface, &p_i->ui_rect[UI_RECT_GUN_SHOOT_2]);
		else if (*timer > 0)
			SDL_BlitSurface(p_i->ui_surface[UI_GUN_SHOOT_1], NULL,
			eng->surface, &p_i->ui_rect[UI_RECT_GUN_SHOOT_1]);
		*timer += delta;
		if (*timer >= 100 || p_i->ammo_gun < 0)
		{
			if (eng->p_i.ammo_gun > 0)
			{
				shoot_bullet(eng);
				eng->p_i.ammo_gun--;
			}
			*timer = -100;
			p_i->shoot_led = 0;
		}
	}
}

void				gun_display(t_engine *eng, t_player_items *p_i,
int delta)
{
	static int		timer = -100;

	if (!eng->p_i.change_gun_led && !p_i->gun_number && !p_i->key_hand)
	{
		if (!p_i->shoot_led && !p_i->gun_load_led &&
		p_i->ammo_per_load_gun != p_i->ammo_gun)
			SDL_BlitSurface(p_i->ui_surface[UI_GUN], NULL,
			eng->surface, &p_i->ui_rect[UI_RECT_GUN]);
		gun_shoot(eng, p_i, delta, &timer);
		gun_reload(eng, p_i, delta);
	}
}
