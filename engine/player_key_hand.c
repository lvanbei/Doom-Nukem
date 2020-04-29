/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_key_hand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:32 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:33 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void			key_down_gun_up(t_engine *eng, t_player_items *p_i,
double delta, int *finish)
{
	static double	up = WIN_HEIGHT;
	static double	down = 567;

	if (p_i->ui_rect[UI_RECT_KEY_HAND].y < WIN_HEIGHT)
	{
		down += ((double)delta / ((0.3 * 1000) / 153.0f));
		p_i->ui_rect[UI_RECT_KEY_HAND].y = down;
	}
	if (p_i->ui_rect[UI_RECT_KEY_HAND].y >= WIN_HEIGHT &&
	p_i->ui_rect[UI_RECT_GUN].y > 567)
	{
		up -= (double)delta / ((0.3 * 1000) / 153.0f);
		p_i->ui_rect[UI_RECT_GUN].y = up;
		SDL_BlitSurface(p_i->ui_surface[UI_GUN], 0,
		eng->surface, &p_i->ui_rect[UI_RECT_GUN]);
	}
	if (p_i->ui_rect[UI_RECT_GUN].y <= 567)
	{
		*finish = 0;
		up = WIN_HEIGHT;
		down = 567;
		p_i->key_hand = 0;
		p_i->activate_doors = 1;
	}
}

static void			key_hand_gun_2(t_engine *eng,
double d, double *down, double *up)
{
	t_player_items	*p_i;

	p_i = &eng->p_i;
	if (p_i->ui_rect[UI_RECT_GUN].y < WIN_HEIGHT)
	{
		*down += ((double)d / ((0.3 * 1000) / 153.0f));
		p_i->ui_rect[UI_RECT_GUN].y = *down;
		SDL_BlitSurface(p_i->ui_surface[UI_GUN], 0,
				eng->surface, &p_i->ui_rect[UI_RECT_GUN]);
	}
	if (p_i->ui_rect[UI_RECT_GUN].y >= WIN_HEIGHT &&
			p_i->ui_rect[UI_RECT_KEY_HAND].y > 567)
	{
		*up -= (double)d / ((0.3 * 1000) / 153.0f);
		p_i->ui_rect[UI_RECT_KEY_HAND].y = *up;
	}
}

static void			key_hand_gun(t_engine *eng, t_player_items *p_i,
double delta)
{
	static double	up = WIN_HEIGHT;
	static double	down = 567;
	static int		finish = 0;
	static double	timer = 0;

	if (!finish)
	{
		timer += delta;
		key_hand_gun_2(eng, delta, &down, &up);
		if (p_i->ui_rect[UI_RECT_KEY_HAND].y <= 567)
		{
			if (timer >= 750)
			{
				finish = 1;
				timer = 0;
			}
			up = WIN_HEIGHT;
			down = 567;
		}
	}
	if (finish)
		key_down_gun_up(eng, p_i, delta, &finish);
}

void				key_hand(t_engine *eng, t_player_items *p_i, double delta)
{
	if (p_i->key_hand == 1 && p_i->activate_doors)
	{
		init_open_walls(eng);
		p_i->activate_doors = 0;
	}
	if (p_i->key_hand == 1 && p_i->gun_number == 0)
		key_hand_gun(eng, p_i, delta);
	if (p_i->key_hand == 1 && p_i->gun_number == 1)
		key_hand_rpg(eng, p_i, delta);
}
