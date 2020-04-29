/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ed.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	init_ed0(t_ed *ed)
{
	ed->view.xmin = -15.0f;
	ed->view.ymin = -15.0f;
	ed->view.w = 30;
	ed->view.dx = GRID_WIDTH / ed->view.w;
	ed->view.dx_1 = ed->view.w / (double)GRID_WIDTH;
	ed->istates.active_tool = TL_WALL;
	ft_strcpy(ed->tool_name[TL_WALL], "WALL");
	ed->tool_textbounds[TL_WALL] = (SDL_Rect) {GRID_WIDTH + 2, 2, 32, 8};
	ft_strcpy(ed->tool_name[TL_THING], "THING");
	ed->tool_textbounds[TL_THING] = (SDL_Rect) {GRID_WIDTH + 2, 12, 40, 8};
	ft_strcpy(ed->tool_name[TL_SELECT_WALL], "SELECT WALL");
	ed->tool_textbounds[TL_SELECT_WALL] = (SDL_Rect)
	{GRID_WIDTH + 2, 22, 88, 8};
	ft_strcpy(ed->tool_name[TL_SELECT_SECTOR], "SELECT SECTOR");
	ed->tool_textbounds[TL_SELECT_SECTOR] = (SDL_Rect)
	{GRID_WIDTH + 2, 32, 104, 8};
	ft_strcpy(ed->tool_name[TL_SELECT_THING], "SELECT THING");
	ed->tool_textbounds[TL_SELECT_THING] = (SDL_Rect)
	{GRID_WIDTH + 2, 42, 96, 8};
	ed->tl_w.num_walls = 0;
	ed->thing_typebounds[TH_PLAYER] = (SDL_Rect) {GRID_WIDTH + 2, 72,
		ed->ed_textures[TH_PLAYER]->w, ed->ed_textures[TH_PLAYER]->h};
}

void	init_ed1(t_ed *ed)
{
	int row2_y;

	ed->thing_typebounds[TH_KEY] =
		(SDL_Rect) {ed->thing_typebounds[TH_PLAYER].x +
			ed->thing_typebounds[TH_PLAYER].w + 2, 72,
			ed->ed_textures[TH_KEY]->w, ed->ed_textures[TH_KEY]->h};
	ed->thing_typebounds[TH_JETPACK_FUEL] =
		(SDL_Rect) {ed->thing_typebounds[TH_KEY].x +
			ed->thing_typebounds[TH_KEY].w + 2, 72,
			ed->ed_textures[TH_JETPACK_FUEL]->w,
			ed->ed_textures[TH_JETPACK_FUEL]->h};
	row2_y = ed->thing_typebounds[TH_PLAYER].y +
		ed->thing_typebounds[TH_PLAYER].h + 2;
	ed->thing_typebounds[TH_AMMO] =
		(SDL_Rect) {GRID_WIDTH + 2, row2_y,
			ed->ed_textures[TH_AMMO]->w, ed->ed_textures[TH_AMMO]->h};
	ed->thing_typebounds[TH_HEAL] =
		(SDL_Rect) {ed->thing_typebounds[TH_AMMO].x +
			ed->thing_typebounds[TH_AMMO].w + 2, row2_y,
			ed->ed_textures[TH_HEAL]->w, ed->ed_textures[TH_HEAL]->h};
	ed->thing_typebounds[TH_MONSTER] =
		(SDL_Rect) {ed->thing_typebounds[TH_HEAL].x +
			ed->thing_typebounds[TH_HEAL].w + 2, 72,
			ed->ed_textures[TH_MONSTER]->w, ed->ed_textures[TH_MONSTER]->h};
}

void	init_ed2(t_ed *ed)
{
	ed->thing_typebounds[TH_RPG] =
		(SDL_Rect) {ed->thing_typebounds[TH_MONSTER].x +
			ed->thing_typebounds[TH_MONSTER].w, 72,
			ed->ed_textures[TH_RPG]->w, ed->ed_textures[TH_RPG]->h};
	ed->thing_typebounds[TH_MOUSE_ENDING] =
		(SDL_Rect) {ed->thing_typebounds[TH_RPG].x,
			ed->thing_typebounds[TH_RPG].y + ed->thing_typebounds[TH_RPG].h +
				2, ed->ed_textures[TH_MOUSE_ENDING]->w,
			ed->ed_textures[TH_MOUSE_ENDING]->h};
	ed->istates.th_hot = TH_NONE;
	ed->istates.th_active = TH_PLAYER;
	ed->tl_w.hot_tex_pick = TXP_NONE;
	ed->tl_w.active_tex_pick = TXP_MAIN;
	ed->tl_w.default_b_texture = 0;
	ed->tl_w.default_m_texture = 0;
	ed->tl_w.default_t_texture = 0;
	ed->tl_w.default_floor_texture = 0;
	ed->tl_w.default_ceiling_texture = 0;
	ed->tl_w.default_floor_height = 0.0f;
	ed->tl_w.default_ceiling_height = 5.0f;
	ed->istates.active_wall = -1;
	ed->istates.hot_wall = -1;
	ed->istates.active_wall_has_co = 0;
	ed->istates.hot_sector = -1;
	ed->istates.active_sector = -1;
}

void	init_ed3(t_ed *ed)
{
	ed->istates.active_thing = -1;
	ed->istates.txp_hot_texture = -1;
	ed->istates.active_slider = -1;
	ed->istates.mb_down[LMB] = 0;
	ed->istates.mb_down[RMB] = 0;
	ed->istates.shift_down = 0;
	ft_strcpy(ed->tex_pick_strs[0], "bottom");
	ed->tex_pick_strsbounds[0] = (SDL_Rect){GRID_WIDTH + 2, 90, 48, 8};
	ft_strcpy(ed->tex_pick_strs[1], "main");
	ed->tex_pick_strsbounds[1] = (SDL_Rect){GRID_WIDTH + 2 +
		ed->tex_pick_strsbounds[0].w + 10, 90, 32, 8};
	ft_strcpy(ed->tex_pick_strs[2], "top");
	ed->tex_pick_strsbounds[2] = (SDL_Rect){GRID_WIDTH + 2 +
		ed->tex_pick_strsbounds[0].w + 10 + ed->tex_pick_strsbounds[1].w + 10,
			90, 24, 8};
	ft_strcpy(ed->tex_pick_strs[3], "floor");
	ed->tex_pick_strsbounds[3] = (SDL_Rect){GRID_WIDTH + 2 +
		ed->tex_pick_strsbounds[0].w + 10 + ed->tex_pick_strsbounds[1].w +
			10 + ed->tex_pick_strsbounds[2].w + 10, 90, 40, 8};
	ft_strcpy(ed->tex_pick_strs[4], "ceiling");
	ed->tex_pick_strsbounds[4] = (SDL_Rect){GRID_WIDTH + 2 +
		ed->tex_pick_strsbounds[0].w + 10 + ed->tex_pick_strsbounds[1].w +
			10 + ed->tex_pick_strsbounds[2].w + 10 +
			ed->tex_pick_strsbounds[3].w + 10, 90, 56, 8};
	ed->texture_pickbounds[0] = (SDL_Rect){GRID_WIDTH + 2, 120, 64, 64};
}

void	init_ed4(t_ed *ed)
{
	ed->texture_pickbounds[1] = (SDL_Rect){GRID_WIDTH + 3 +
		ed->texture_pickbounds[0].w, 120, 64, 64};
	ed->texture_pickbounds[2] = (SDL_Rect){GRID_WIDTH + 4 +
		ed->texture_pickbounds[0].w + ed->texture_pickbounds[1].w,
			120, 64, 64};
	ed->texture_pickbounds[3] = (SDL_Rect){GRID_WIDTH + 5 +
		ed->texture_pickbounds[0].w + ed->texture_pickbounds[1].w +
			ed->texture_pickbounds[2].w, 120, 64, 64};
	ed->texture_pickbounds[4] = (SDL_Rect){GRID_WIDTH + 2,
		120 + ed->texture_pickbounds[0].h, 64, 64};
	ed->texture_pickbounds[5] = (SDL_Rect){GRID_WIDTH + 3 +
		ed->texture_pickbounds[0].w,
		120 + ed->texture_pickbounds[0].h, 64, 64};
	ed->texture_pickbounds[6] = (SDL_Rect){GRID_WIDTH + 4 +
		ed->texture_pickbounds[0].w + ed->texture_pickbounds[1].w,
		120 + ed->texture_pickbounds[0].h, 64, 64};
	ed->texture_pickbounds[7] = (SDL_Rect){GRID_WIDTH + 5 +
		ed->texture_pickbounds[0].w + ed->texture_pickbounds[1].w +
			ed->texture_pickbounds[2].w,
		120 + ed->texture_pickbounds[0].h, 64, 64};
}
