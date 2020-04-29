/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_menu2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		tool_switch2(t_ed *ed, int i)
{
	ed->istates.active_tool = i;
	ed->istates.active_wall = -1;
	ed->istates.active_thing = -1;
	ed->istates.active_sector = -1;
}

void		tool_switch(t_ed *ed, SDL_Event *e)
{
	int	i;

	i = -1;
	while (++i < TL_END)
	{
		if (point_in_rect(ed->istates.mouse_x, ed->istates.mouse_y,
					&ed->tool_textbounds[i]))
		{
			if (was_pressed(&ed->istates, e, LMB))
			{
				if (ed->istates.active_tool == TL_WALL && i != TL_WALL)
					ed->tl_w.num_walls = 0;
				if (i == TL_SELECT_SECTOR)
					ed->tl_w.active_tex_pick = TXP_FLOOR;
				else
					ed->tl_w.active_tex_pick = TXP_MAIN;
				tool_switch2(ed, i);
			}
			else
				ed->istates.hot_tool = i;
			break ;
		}
	}
}

void		texture_picker_click2(t_ed *ed, SDL_Event *e,
		t_context_menu *m)
{
	int j;

	j = -1;
	while (++j < NUM_TEXTURES + 1)
	{
		if (point_in_rect(ed->istates.mouse_x, ed->istates.mouse_y,
					&ed->texture_pickbounds[j]))
		{
			if (was_pressed(&ed->istates, e, LMB))
				*(m->tex_pick_p)[ed->tl_w.active_tex_pick] = j - 1;
			else
				ed->istates.txp_hot_texture = j;
		}
	}
}

void		texture_picker_click(t_ed *ed, SDL_Event *e, t_context_menu *m)
{
	int	start_pick_strs;
	int	num_text_pick_strs;
	int	j;

	start_pick_strs = TXP_BOT;
	num_text_pick_strs = TXP_END;
	if (ed->istates.active_tool == TL_SELECT_SECTOR)
		start_pick_strs = TXP_FLOOR;
	else if (ed->istates.active_tool == TL_SELECT_WALL)
		num_text_pick_strs = 3;
	j = start_pick_strs - 1;
	while (++j < num_text_pick_strs)
	{
		if (point_in_rect(ed->istates.mouse_x, ed->istates.mouse_y,
					&ed->tex_pick_strsbounds[j]))
		{
			if (was_pressed(&ed->istates, e, LMB))
				ed->tl_w.active_tex_pick = j;
			else
				ed->tl_w.hot_tex_pick = j;
		}
	}
	texture_picker_click2(ed, e, m);
}
