/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_key_hand_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:37 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:34 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void			key_down_rpg_up(t_engine *eng, t_player_items *p_i,
double delta, int *finish)
{
	static double	down = 593;
	static double	up = WIN_HEIGHT;

	if (p_i->ui_rect[UI_RECT_KEY_HAND].y < WIN_HEIGHT)
	{
		down += ((double)delta / ((0.3 * 1000) / 97.0f));
		p_i->ui_rect[UI_RECT_KEY_HAND].y = down;
	}
	if (p_i->ui_rect[UI_RECT_KEY_HAND].y >= WIN_HEIGHT &&
			p_i->ui_rect[UI_RECT_RPG_1].y > 593)
	{
		up -= (double)delta / ((0.3 * 1000) / 97.0f);
		p_i->ui_rect[UI_RECT_RPG_1].y = up;
		SDL_BlitSurface(p_i->ui_surface[UI_RPG_1], 0, eng->surface,
				&p_i->ui_rect[UI_RECT_RPG_1]);
	}
	if (p_i->ui_rect[UI_RECT_RPG_1].y <= 593)
	{
		up = WIN_HEIGHT;
		down = 593;
		p_i->key_hand = 0;
		*finish = 0;
		p_i->activate_doors = 1;
	}
}

static void			key_hand_rpg_2(t_engine *eng, t_player_items *p_i,
		double delta, double *down)
{
	if (p_i->ui_rect[UI_RECT_RPG_1].y < WIN_HEIGHT)
	{
		*down += ((double)delta / ((0.3 * 1000) / 97.0f));
		p_i->ui_rect[UI_RECT_RPG_1].y = *down;
		SDL_BlitSurface(p_i->ui_surface[UI_RPG_1], 0,
				eng->surface, &p_i->ui_rect[UI_RECT_RPG_1]);
	}
}

static void			key_hand_rpg_3(t_player_items *p_i, double d, double *up)
{
	if (p_i->ui_rect[UI_RECT_RPG_1].y >= WIN_HEIGHT &&
			p_i->ui_rect[UI_RECT_KEY_HAND].y > 593)
	{
		*up -= (double)d / ((0.3 * 1000) / 97.0f);
		p_i->ui_rect[UI_RECT_KEY_HAND].y = *up;
	}
	if (p_i->ui_rect[UI_RECT_RPG_1].y >= WIN_HEIGHT &&
			p_i->ui_rect[UI_RECT_KEY_HAND].y > 593)
	{
		*up -= (double)d / ((0.3 * 1000) / 97.0f);
		p_i->ui_rect[UI_RECT_KEY_HAND].y = *up;
	}
}

void				key_hand_rpg(t_engine *eng, t_player_items *p_i,
double delta)
{
	static double	up = WIN_HEIGHT;
	static int		finish = 0;
	static double	down = 593;
	static double	timer = 0;

	if (!finish)
	{
		timer += delta;
		key_hand_rpg_2(eng, p_i, delta, &down);
		key_hand_rpg_3(p_i, delta, &up);
		if (p_i->ui_rect[UI_RECT_KEY_HAND].y <= 593)
		{
			if (timer >= 750)
			{
				finish = 1;
				timer = 0;
			}
			up = WIN_HEIGHT;
			down = 593;
		}
	}
	if (finish)
		key_down_rpg_up(eng, p_i, delta, &finish);
}
