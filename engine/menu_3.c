/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:37 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:34 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void			keys_event_2(int *ret, t_engine *eng,
t_menu *menu)
{
	if (menu->y == 368 && eng->key_states[SDL_SCANCODE_RETURN]
	&& !menu->which_menu)
		exit(1);
	if (menu->y == 248 && eng->key_states[SDL_SCANCODE_RETURN]
	&& !menu->which_menu)
	{
		menu->which_menu = 1;
		*ret = 1;
	}
}

void				keys_event(SDL_Event *event, int *ret, t_engine *eng,
t_menu *menu)
{
	if ((event->type == SDL_QUIT && event->key.repeat == 0) ||
	(eng->key_states[SDL_SCANCODE_ESCAPE] && !menu->which_menu))
		exit(1);
	if (!menu->go_game)
	{
		if (eng->key_states[SDL_SCANCODE_ESCAPE] && menu->which_menu)
		{
			menu->which_menu = 0;
			*ret = 1;
		}
		if (eng->key_states[SDL_SCANCODE_DOWN] && event->key.repeat == 0)
			menu->y += 120;
		if (eng->key_states[SDL_SCANCODE_UP] && event->key.repeat == 0)
			menu->y -= 120;
		if ((eng->key_states[SDL_SCANCODE_RETURN]) && ((menu->y == 128 &&
		!menu->which_menu) || menu->which_menu))
		{
			menu->go_game = !menu->go_game;
			menu->game_hardless = menu->y / 120;
			*ret = 1;
		}
		keys_event_2(ret, eng, menu);
	}
}

void				load_rect_menu(t_menu *menu)
{
	menu->rect[MENU_RECT_START] = (SDL_Rect){340 - 350 / 2, 138, 350, 100};
	menu->rect[MENU_RECT_SETTINGS] = (SDL_Rect){340 - 400 / 2, 258, 400, 100};
	menu->rect[MENU_RECT_EXIT] = (SDL_Rect){340 - 300 / 2, 378, 300, 100};
	menu->rect[MENU_RECT_EASY] = (SDL_Rect){340 - 300 / 2, 138, 300, 100};
	menu->rect[MENU_RECT_MEDIUM] = (SDL_Rect){340 - 400 / 2, 258, 400, 100};
	menu->rect[MENU_RECT_HARD] = (SDL_Rect){340 - 300 / 2, 378, 300, 100};
	menu->rect[MENU_RECT_DOOR_UP] = (SDL_Rect){0, -340, 680, 340};
	menu->rect[MENU_RECT_DOOR_DOWN] = (SDL_Rect){0, 680, 680, 340};
}

static void			init_cursor_rect_2(t_menu *menu, int led)
{
	if (!led)
	{
		menu->rect[MENU_RECT_SELECTOR_1] = (SDL_Rect){WIN_WIDTH - (menu->x +
		(119)) - 40, menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2),
		119, 100};
		menu->rect[MENU_RECT_SELECTOR_2] = (SDL_Rect){WIN_WIDTH - (menu->x +
		(119) + 3) - 40, menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2),
		110, 100};
		menu->rect[MENU_RECT_SELECTOR_3] = (SDL_Rect){WIN_WIDTH - (menu->x +
		(119) + 6) - 40, menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2),
		90, 100};
		menu->rect[MENU_RECT_SELECTOR_4] = (SDL_Rect){WIN_WIDTH - (menu->x +
		(119) + 9) - 40, menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2),
		62, 100};
		menu->rect[MENU_RECT_SELECTOR_5] = (SDL_Rect){WIN_WIDTH - (menu->x +
		(119) + 19) - 40, menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2),
		19, 100};
		menu->rect[MENU_RECT_SELECTOR_6] = (SDL_Rect){WIN_WIDTH - (menu->x +
		(119)) - 40, menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2), 52,
		100};
		menu->rect[MENU_RECT_SELECTOR_7] = (SDL_Rect){WIN_WIDTH - (menu->x +
		(119)) - 40, menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2), 90,
		100};
	}
}

void				init_cursor_rect(t_menu *menu, int led)
{
	if (led)
	{
		menu->rect[MENU_RECT_SELECTOR_1] = (SDL_Rect){menu->x + (119 / 2),
		menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2), 119, 100};
		menu->rect[MENU_RECT_SELECTOR_2] = (SDL_Rect){menu->x + (119 / 2) + 3,
		menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2), 110, 100};
		menu->rect[MENU_RECT_SELECTOR_3] = (SDL_Rect){menu->x + (119 / 2) + 6,
		menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2), 90, 100};
		menu->rect[MENU_RECT_SELECTOR_4] = (SDL_Rect){menu->x + (119 / 2) + 9,
		menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2), 62, 100};
		menu->rect[MENU_RECT_SELECTOR_5] = (SDL_Rect){menu->x + (119 / 2) + 19,
		menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2), 19, 100};
		menu->rect[MENU_RECT_SELECTOR_6] = (SDL_Rect){menu->x + (119 / 2),
		menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2), 52, 100};
		menu->rect[MENU_RECT_SELECTOR_7] = (SDL_Rect){menu->x + (119 / 2),
		menu->y + (menu->surfaces[MENU_SELECTOR_1]->h / 2), 90, 100};
	}
	init_cursor_rect_2(menu, led);
}
