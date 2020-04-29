/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:02 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 10:47:36 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	free_assets2(t_ed *ed)
{
	int i;

	i = UI_NUMBER_0_0;
	while (i <= UI_WIN)
	{
		if (ed->player_ui_surfaces[i] != NULL)
			SDL_FreeSurface(ed->player_ui_surfaces[i]);
		i++;
	}
	i = UI_SOUND_GUN_SHOOT;
	while (i <= UI_SOUND_DIE)
	{
		if (ed->ui_sound[i] != NULL)
			Mix_FreeChunk(ed->ui_sound[i]);
		i++;
	}
}

void	free_assets(t_ed *ed)
{
	int i;

	i = UI_PLAYER;
	while (i <= UI_IMPACT)
	{
		if (ed->ed_textures[i] != NULL)
			SDL_FreeSurface(ed->ed_textures[i]);
		i++;
	}
	i = 0;
	while (i <= 6)
	{
		if (ed->textures[i] != NULL)
			SDL_FreeSurface(ed->textures[i]);
		i++;
	}
	i = MENU_BACK_GROUND;
	while (i <= MENU_DOOR_DOWN)
	{
		if (ed->menu_surfaces[i] != NULL)
			SDL_FreeSurface(ed->menu_surfaces[i]);
		i++;
	}
	free_assets2(ed);
}

void	abort_error(t_ed *ed, char *str, ...)
{
	va_list args;

	if (ed)
		free_assets(ed);
	va_start(args, str);
	ft_printf("error: ");
	ft_vprintf(str, args);
	ft_printf("\n");
	va_end(args);
	exit(-1);
}
