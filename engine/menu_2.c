/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:37 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:34 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int			move_doors_2(t_engine *eng, t_menu *menu, int *finish)
{
	if (*finish == 1)
	{
		menu->timer_plus += (double)menu->delta / ((1 * 1000) / 340);
		menu->timer_min -= (double)menu->delta / ((1 * 1000) / 340);
		menu->rect[MENU_RECT_DOOR_UP].y = menu->timer_min;
		menu->rect[MENU_RECT_DOOR_DOWN].y = menu->timer_plus;
	}
	if (*finish == 1)
		slow_bzero(eng->surface->pixels, (WIN_HEIGHT) * (WIN_WIDTH) * 4);
	if (*finish == 1 && menu->timer_min <= -340.0f &&
	menu->timer_plus >= 680.0f)
	{
		slow_bzero(eng->surface->pixels, (WIN_HEIGHT) * (WIN_WIDTH) * 4);
		menu->timer_plus = -340.0f;
		menu->timer_min = 680.0f;
		*finish = 0;
		return (0);
	}
	SDL_BlitSurface(menu->surfaces[MENU_DOOR_UP], 0, eng->surface,
	&menu->rect[MENU_RECT_DOOR_UP]);
	SDL_BlitSurface(menu->surfaces[MENU_DOOR_DOWN], 0, eng->surface,
	&menu->rect[MENU_RECT_DOOR_DOWN]);
	return (1);
}

int					move_doors(t_engine *eng, int delta, t_menu *menu)
{
	static int		finish = 0;

	if (finish == 0)
	{
		menu->timer_plus += (double)delta / ((1 * 1000) / 340);
		menu->timer_min -= (double)delta / ((1 * 1000) / 340);
		menu->rect[MENU_RECT_DOOR_UP].y = menu->timer_plus;
		menu->rect[MENU_RECT_DOOR_DOWN].y = menu->timer_min;
	}
	if (menu->timer_plus >= 0 && menu->timer_min <= 340.0f)
	{
		if (finish == 0)
		{
			menu->timer_min = 0;
			menu->timer_plus = 340.0f;
		}
		finish = 1;
	}
	return (move_doors_2(eng, menu, &finish));
}

static void			cursor_animation_2(t_menu *menu, t_engine *eng,
int *timer_s, int range)
{
	if (*timer_s > 6 * range && *timer_s <= 7 * range)
		SDL_BlitScaled(menu->surfaces[MENU_SELECTOR_7], 0, eng->surface,
		&menu->rect[MENU_RECT_SELECTOR_7]);
	if (*timer_s > 7 * range)
		*timer_s = 0;
}

void				cursor_animation(t_menu *menu, t_engine *eng,
int delta, int delta_inc)
{
	static int		timer_s = 0;
	int				range;

	range = 100;
	if (delta_inc == 1)
		timer_s += delta;
	if (timer_s <= 1 * range)
		SDL_BlitScaled(menu->surfaces[MENU_SELECTOR_1], 0, eng->surface,
		&menu->rect[MENU_RECT_SELECTOR_1]);
	else if (timer_s > 1 * range && timer_s <= 2 * range)
		SDL_BlitScaled(menu->surfaces[MENU_SELECTOR_2], 0, eng->surface,
		&menu->rect[MENU_RECT_SELECTOR_2]);
	else if (timer_s > 2 * range && timer_s <= 3 * range)
		SDL_BlitScaled(menu->surfaces[MENU_SELECTOR_3], 0, eng->surface,
		&menu->rect[MENU_RECT_SELECTOR_3]);
	else if (timer_s > 3 * range && timer_s <= 4 * range)
		SDL_BlitScaled(menu->surfaces[MENU_SELECTOR_4], 0, eng->surface,
		&menu->rect[MENU_RECT_SELECTOR_4]);
	else if (timer_s > 4 * range && timer_s <= 5 * range)
		SDL_BlitScaled(menu->surfaces[MENU_SELECTOR_5], 0, eng->surface,
		&menu->rect[MENU_RECT_SELECTOR_5]);
	else if (timer_s > 5 * range && timer_s <= 6 * range)
		SDL_BlitScaled(menu->surfaces[MENU_SELECTOR_6], 0, eng->surface,
		&menu->rect[MENU_RECT_SELECTOR_6]);
	cursor_animation_2(menu, eng, &timer_s, range);
}
