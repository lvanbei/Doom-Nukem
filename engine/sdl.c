/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:23:38 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:47:13 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void		sdl_init(t_engine *eng)
{
	int	i;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	eng->window = SDL_CreateWindow("doom-nukem", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT,
			SDL_WINDOW_INPUT_FOCUS);
	if (eng->window == NULL)
		abort_error(eng, "%s", SDL_GetError());
	eng->surface = SDL_GetWindowSurface(eng->window);
	if (eng->surface == NULL)
		abort_error(eng, "%s", SDL_GetError());
	slow_bzero(eng->surface->pixels, WIN_WIDTH * WIN_HEIGHT * 4);
	eng->key_states = SDL_GetKeyboardState(NULL);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_UpdateWindowSurface(eng->window);
	i = -1;
	while (++i < eng->num_textures)
		eng->textures[i] = SDL_ConvertSurface(eng->textures[i],
				eng->surface->format, 0);
}

void		sdl_init_audio(void)
{
	if (Mix_OpenAudio(44800, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		abort_error(NULL, "Mix_OpenAudio failed: %s\n", Mix_GetError());
}

void		sdl_shutdown(SDL_Window *window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}
