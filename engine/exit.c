/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:20:30 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/04 12:46:50 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	free_assets3(t_engine *eng)
{
	int i;

	i = -1;
	if (eng->p_i.ui_sound)
	{
		while (++i < UI_SOUND_END)
		{
			if (eng->p_i.ui_sound[i])
				Mix_FreeChunk(eng->p_i.ui_sound[i]);
		}
		free(eng->p_i.ui_sound);
	}
}

void	free_assets2(t_engine *eng)
{
	int i;

	i = -1;
	if (eng->menu.surfaces)
	{
		while (++i < MENU_SURFACE_END)
		{
			if (eng->menu.surfaces[i])
				SDL_FreeSurface(eng->menu.surfaces[i]);
		}
		free(eng->menu.surfaces);
	}
	if (eng->p_i.ui_surface)
	{
		i = -1;
		while (++i < UI_SURFACES_END)
		{
			if (eng->p_i.ui_surface[i])
				SDL_FreeSurface(eng->p_i.ui_surface[i]);
		}
		free(eng->p_i.ui_surface);
	}
	free_assets3(eng);
}

void	free_assets(t_engine *eng)
{
	int i;

	i = -1;
	if (eng->textures)
	{
		while (++i < eng->num_textures)
		{
			if (eng->textures[i])
				SDL_FreeSurface(eng->textures[i]);
		}
		free(eng->textures);
	}
	if (eng->thing_textures)
	{
		i = -1;
		while (++i < eng->num_thing_textures)
		{
			if (eng->thing_textures[i])
				SDL_FreeSurface(eng->thing_textures[i]);
		}
		free(eng->thing_textures);
	}
	free_assets2(eng);
}

void	abort_error(t_engine *eng, char *str, ...)
{
	va_list args;

	if (eng)
		free_assets(eng);
	va_start(args, str);
	ft_printf("error: ");
	ft_vprintf(str, args);
	ft_printf("\n");
	va_end(args);
	exit(-1);
}
