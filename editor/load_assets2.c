/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		check_assets2(t_ed *ed)
{
	int	i;

	i = -1;
	while (++i < UI_SURFACES_END)
	{
		if (ed->player_ui_surfaces[i] == NULL)
			abort_error(ed, "player ui surfaces: %d\n", i);
	}
}

void		check_assets(t_ed *ed)
{
	int	i;

	i = -1;
	while (++i < UI_END)
	{
		if (ed->ed_textures[i] == NULL)
			abort_error(ed, "ed_texture: %d", i);
	}
	i = -1;
	while (++i < NUM_TEXTURES)
	{
		if (ed->textures[i] == NULL)
			abort_error(ed, "texture: %d\n", i);
	}
	i = -1;
	while (++i < MENU_SURFACE_END)
	{
		if (ed->menu_surfaces[i] == NULL)
			abort_error(ed, "menu_surfaces: %d\n", i);
	}
	check_assets2(ed);
}

void		load_assets5(t_ed *ed)
{
	if (ed->ui_sound[UI_SOUND_JP_3] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
	ed->ui_sound[UI_SOUND_GET_ITEM] = Mix_LoadWAV("audio/getitem.WAV");
	if (ed->ui_sound[UI_SOUND_GET_ITEM] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
	ed->ui_sound[UI_SOUND_MENU] = Mix_LoadWAV("audio/menu_song.WAV");
	if (ed->ui_sound[UI_SOUND_MENU] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
	ed->ui_sound[UI_SOUND_EXPLODE] = Mix_LoadWAV("audio/explode3.wav");
	if (ed->ui_sound[UI_SOUND_EXPLODE] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
	ed->ui_sound[UI_SOUND_DOORMOVE] = Mix_LoadWAV("audio/doormove2.wav");
	if (ed->ui_sound[UI_SOUND_DOORMOVE] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
	ed->ui_sound[UI_SOUND_BUTTON] = Mix_LoadWAV("audio/button6.wav");
	if (ed->ui_sound[UI_SOUND_BUTTON] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
	ed->ui_sound[UI_SOUND_DIE] = Mix_LoadWAV("audio/ag_die2.wav");
	if (ed->ui_sound[UI_SOUND_DIE] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
}

void		load_assets4(t_ed *ed)
{
	ed->ui_sound[UI_SOUND_GUN_SHOOT] = Mix_LoadWAV("audio/gun_shoot.WAV");
	if (ed->ui_sound[UI_SOUND_GUN_SHOOT] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
	ed->ui_sound[UI_SOUND_GUN_RELOAD_1] = Mix_LoadWAV("audio/gun_reload_1.WAV");
	if (ed->ui_sound[UI_SOUND_GUN_RELOAD_1] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
	ed->ui_sound[UI_SOUND_RPG_SHOOT] = Mix_LoadWAV("audio/rpg_shoot.WAV");
	if (ed->ui_sound[UI_SOUND_RPG_SHOOT] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
	ed->ui_sound[UI_SOUND_JP_1] = Mix_LoadWAV("audio/jp_on.WAV");
	if (ed->ui_sound[UI_SOUND_JP_1] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
	ed->ui_sound[UI_SOUND_JP_2] = Mix_LoadWAV("audio/jp_stable.WAV");
	if (ed->ui_sound[UI_SOUND_JP_2] == NULL)
		abort_error(ed, "Mix: %s\n", Mix_GetError());
	ed->ui_sound[UI_SOUND_JP_3] = Mix_LoadWAV("audio/jp_off.WAV");
}
