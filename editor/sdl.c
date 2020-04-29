/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		init_alpha_filter_surface(SDL_Surface *src, t_mask m)
{
	uint32_t	color;
	int			x;
	int			y;

	color = SDL_MapRGBA(src->format, m.r, m.g, m.b, m.alpha);
	x = 0;
	while (++x < WIN_WIDTH)
	{
		y = 0;
		while (++y < WIN_HEIGHT)
			((uint32_t *)src->pixels)[x + (WIN_WIDTH) * y] = color;
	}
}

void		sdl_init(t_ed *ed)
{
	SDL_Init(SDL_INIT_VIDEO);
	ed->window = SDL_CreateWindow("editor", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT,
			SDL_WINDOW_INPUT_FOCUS);
	if (ed->window == NULL)
		abort_error(ed, "%s\n", SDL_GetError());
	ed->surface = SDL_GetWindowSurface(ed->window);
	if (ed->surface == NULL)
		abort_error(ed, "%s\n", SDL_GetError());
	slow_bzero(ed->surface->pixels, WIN_WIDTH * WIN_HEIGHT * 4);
	if (Mix_Init(0) != 0)
		abort_error(ed, "Couldn't load SDL_mixer: %s\n", Mix_GetError());
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		abort_error(ed, "Mix_OpenAudio failed: %s\n", Mix_GetError());
	load_assets(ed);
	SDL_UpdateWindowSurface(ed->window);
}

void		sdl_shutdown(SDL_Window *window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}
