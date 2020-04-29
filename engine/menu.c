/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:37 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:34 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void				check_cursor_height(t_menu *menu)
{
	if (menu->y < 128)
		menu->y = 368;
	if (menu->y >= 488)
		menu->y = 128;
	if (menu->y == 128)
		menu->x = -15;
	if (menu->y == 248)
		menu->x = -40;
	if (menu->y == 368)
		menu->x = 5;
}

void				main_menu(t_menu *menu, int ret, int delta, t_engine *eng)
{
	if (ret == 0 || ret == -1)
	{
		SDL_BlitSurface(menu->surfaces[MENU_BACK_GROUND], NULL,
		eng->surface, NULL);
		SDL_BlitScaled(menu->surfaces[MENU_START], NULL,
		eng->surface, &menu->rect[MENU_RECT_START]);
		SDL_BlitScaled(menu->surfaces[MENU_SETTINGS], NULL,
		eng->surface, &menu->rect[MENU_RECT_SETTINGS]);
		SDL_BlitScaled(menu->surfaces[MENU_EXIT], NULL,
		eng->surface, &menu->rect[MENU_RECT_EXIT]);
		init_cursor_rect(menu, 1);
		cursor_animation(menu, eng, delta, 1);
		init_cursor_rect(menu, 0);
		cursor_animation(menu, eng, delta, 0);
	}
}

void				second_menu(t_menu *menu, int ret, int delta, t_engine *eng)
{
	if (ret == 0)
	{
		slow_bzero(eng->surface->pixels, (WIN_HEIGHT) * (WIN_WIDTH) * 4);
		SDL_BlitSurface(menu->surfaces[MENU_BACK_GROUND], NULL,
		eng->surface, NULL);
		SDL_BlitScaled(menu->surfaces[MENU_EASY], NULL,
		eng->surface, &menu->rect[MENU_RECT_EASY]);
		SDL_BlitScaled(menu->surfaces[MENU_MEDIUM], NULL,
		eng->surface, &menu->rect[MENU_RECT_MEDIUM]);
		SDL_BlitScaled(menu->surfaces[MENU_HARD], NULL,
		eng->surface, &menu->rect[MENU_RECT_HARD]);
		init_cursor_rect(menu, 1);
		cursor_animation(menu, eng, delta, 1);
		init_cursor_rect(menu, 0);
		cursor_animation(menu, eng, delta, 0);
	}
}

int					in_menu(t_menu *menu, int delta, t_engine *eng, int ret)
{
	if (menu->go_game == 0)
	{
		if (menu->which_menu == 0)
		{
			if (ret == 1)
				ret = move_doors(eng, delta, menu);
			main_menu(menu, ret, delta, eng);
		}
		if (menu->which_menu == 1)
		{
			if (ret == 1)
				ret = move_doors(eng, delta, menu);
			second_menu(menu, ret, delta, eng);
		}
	}
	return (ret);
}

void				menu(t_engine *eng, t_menu *menu)
{
	SDL_Event		event;
	uint32_t		last_time;
	uint32_t		current_time;

	load_rect_menu(menu);
	init_var_menu(menu);
	current_time = 0;
	last_time = 0;
	menu->delta = 0;
	while (1)
	{
		while (SDL_PollEvent(&event))
			keys_event(&event, &menu->ret, eng, menu);
		current_time = SDL_GetTicks();
		menu->delta = (current_time - last_time);
		last_time = current_time;
		menu_audio(menu->delta, eng);
		check_cursor_height(menu);
		menu->ret = in_menu(menu, menu->delta, eng, menu->ret);
		if (menu->go_game)
			if (!move_doors(eng, menu->delta, menu))
				break ;
		SDL_UpdateWindowSurface(eng->window);
	}
	Mix_HaltChannel(-1);
}
