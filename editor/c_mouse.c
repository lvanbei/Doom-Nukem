/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_mouse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			handle_mouse2(t_ed *ed, SDL_Event *e)
{
	if (was_pressed(&ed->istates, e, LMB))
		;
	else if (was_released(&ed->istates, e, LMB))
	{
		if (ed->istates.active_tool == TL_WALL)
			tl_wall(ed, ed->istates.mouse_x, ed->istates.mouse_y);
		else if (ed->istates.active_tool == TL_THING)
			tl_thing(ed, ed->istates.mouse_x, ed->istates.mouse_y);
		else if (ed->istates.active_tool == TL_SELECT_WALL)
			tl_select_wall(ed, ed->istates.mouse_x, ed->istates.mouse_y, 1);
		else if (ed->istates.active_tool == TL_SELECT_SECTOR)
			tl_select_sector(ed, ed->istates.mouse_x, ed->istates.mouse_y, 1);
		else if (ed->istates.active_tool == TL_SELECT_THING)
			tl_select_thing(ed, ed->istates.mouse_x, ed->istates.mouse_y);
	}
	if (ed->istates.active_tool == TL_SELECT_WALL)
		tl_select_wall(ed, ed->istates.mouse_x, ed->istates.mouse_y, 0);
	else if (ed->istates.active_tool == TL_SELECT_SECTOR)
		tl_select_sector(ed, ed->istates.mouse_x, ed->istates.mouse_y, 0);
}

void			handle_mouse3(t_ed *ed, SDL_Event *e)
{
	if (was_pressed(&ed->istates, e, RMB))
	{
		if (ed->istates.active_tool == TL_SELECT_WALL)
			gather_walls(ed, ed->istates.mouse_x, ed->istates.mouse_y);
	}
	else if (was_released(&ed->istates, e, RMB))
	{
		if (ed->istates.active_tool == TL_SELECT_WALL)
			release_walls(ed, ed->istates.mouse_x, ed->istates.mouse_y);
	}
	if (ed->istates.space_nav && e->motion.type == SDL_MOUSEMOTION)
	{
		ed->view.xmin += (-e->motion.xrel * ed->view.dx_1);
		ed->view.ymin += (e->motion.yrel * ed->view.dx_1);
	}
}

void			handle_mouse(t_ed *ed, SDL_Event *e)
{
	ed->istates.mouse_x = e->motion.x;
	ed->istates.mouse_y = e->motion.y;
	ed->istates.hot_tool = TL_NONE;
	ed->istates.txp_hot_texture = -1;
	ed->istates.th_hot = TH_NONE;
	ed->istates.hot_sector = -1;
	ed->tl_w.hot_tex_pick = TXP_NONE;
	if (ed->istates.mouse_x < GRID_WIDTH)
	{
		ed->istates.active_slider = -1;
		handle_mouse2(ed, e);
		handle_mouse3(ed, e);
	}
	else
	{
		menu_interactions(ed, e);
		was_pressed(&ed->istates, e, LMB);
		was_released(&ed->istates, e, LMB);
		was_pressed(&ed->istates, e, RMB);
		was_released(&ed->istates, e, RMB);
	}
}
