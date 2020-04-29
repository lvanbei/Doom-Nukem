/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_loop_player_items.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:13:14 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/04 18:13:16 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void				blit_pannels(t_engine *eng, t_player_items *p_i)
{
	SDL_BlitSurface(p_i->ui_surface[UI_HEALTH_PANNEL], NULL,
	eng->surface, &p_i->ui_rect[UI_RECT_HEALTH_PANNEL]);
	SDL_BlitSurface(p_i->ui_surface[UI_AMMO_PANNEL], NULL,
	eng->surface, &p_i->ui_rect[UI_RECT_AMMO_PANNEL]);
	SDL_BlitSurface(p_i->ui_surface[UI_INV_PANNEL], NULL,
	eng->surface, &p_i->ui_rect[UI_RECT_INV_PANNEL]);
}

void				blit_scoop(t_engine *eng, t_player_items *p_i)
{
	if (p_i->gun_number == 0 && p_i->key_hand == 0)
		SDL_BlitSurface(p_i->ui_surface[UI_SCOOP_1], NULL,
		eng->surface, &p_i->ui_rect[UI_RECT_SCOOP_1]);
	if (p_i->gun_number == 1)
		SDL_BlitSurface(p_i->ui_surface[UI_SCOOP_2], NULL,
		eng->surface, &p_i->ui_rect[UI_RECT_SCOOP_2]);
}

void				blit_alpha_surface(t_engine *eng, t_player_items *p_i,
int delta)
{
	static int		timer0 = 0;
	static int		timer1 = 0;

	if (p_i->life_led == 1)
	{
		timer0 += delta;
		SDL_BlitSurface(p_i->ui_surface[UI_HIT_ALPHA_RED], 0, eng->surface, 0);
		if (timer0 >= 500)
		{
			p_i->life_led = 0;
			timer0 = 0;
		}
	}
	if (p_i->find_item_led == 1 || timer1 > 0)
	{
		timer1 += delta;
		SDL_BlitSurface(p_i->ui_surface[UI_GET_ALPHA_GREEN],
		0, eng->surface, 0);
		if (timer1 >= 238)
			timer1 = 0;
		p_i->find_item_led = 0;
	}
}

void				update_key_hand(t_engine *eng, t_player_items *p_i)
{
	if (p_i->inv_items[UI_ITEM_KEY] == 1 && p_i->key_hand == 0)
		SDL_BlitSurface(p_i->ui_surface[UI_KEY], 0, eng->surface,
		&p_i->ui_rect[UI_RECT_KEY]);
	if (p_i->ui_rect[UI_RECT_KEY_HAND].y <= WIN_HEIGHT)
		SDL_BlitSurface(p_i->ui_surface[UI_KEY_HAND], 0, eng->surface,
		&p_i->ui_rect[UI_RECT_KEY_HAND]);
}

void				blit_player_items(t_engine *eng, t_player_items *p_i,
int delta, int *pause)
{
	update_life(p_i, delta, pause);
	gun_display(eng, p_i, delta);
	rpg_display_shoot(eng, p_i, delta);
	blit_pannels(eng, p_i);
	blit_number(eng, p_i->life, 0, 0);
	blit_number(eng, !p_i->gun_number ? p_i->ammo_gun : p_i->ammo_rpg, 4, 0);
	update_jetpack(eng, p_i);
	blit_scoop(eng, p_i);
	blit_alpha_surface(eng, p_i, delta);
	update_key_hand(eng, p_i);
}
