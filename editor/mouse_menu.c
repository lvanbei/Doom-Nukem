/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		thing_picker(t_ed *ed, SDL_Event *e)
{
	int	j;

	j = -1;
	while (++j < TH_VISIBLE_END)
	{
		if (point_in_rect(ed->istates.mouse_x, ed->istates.mouse_y,
					&ed->thing_typebounds[j]))
		{
			if (was_pressed(&ed->istates, e, LMB))
				ed->istates.th_active = j;
			else
				ed->istates.th_hot = j;
			break ;
		}
	}
}

static void		variable_control(t_ed *ed, SDL_Event *e, t_context_menu *m)
{
	int	j;

	if (was_released(&ed->istates, e, LMB))
		ed->istates.active_slider = -1;
	if (ed->istates.active_slider != -1 && e->motion.type == SDL_MOUSEMOTION
			&& ed->things[ed->istates.active_thing].type != TH_MONSTER)
		*(m->var_control[ed->istates.active_slider]) =
			f_clamp(m->var_control_clamp[ed->istates.active_slider][0],
					*(m->var_control[ed->istates.active_slider]) +
					(e->motion.xrel / SLIDER_SENSITIVITY),
					m->var_control_clamp[ed->istates.active_slider][1]);
	j = -1;
	while (++j < m->num_var_controls)
	{
		if (point_in_rect(ed->istates.mouse_x, ed->istates.mouse_y,
					&m->var_control_bounds[j]))
		{
			if (was_pressed(&ed->istates, e, LMB))
				ed->istates.active_slider = j;
		}
	}
}

static void		ui_button_click(t_ed *ed, SDL_Event *e, t_context_menu *m)
{
	int	j;

	j = 0;
	while (m->button_action[j] != NULL)
	{
		if (point_in_rect(ed->istates.mouse_x, ed->istates.mouse_y,
					&m->button_bounds[j]))
		{
			if (was_pressed(&ed->istates, e, LMB))
			{
				m->button_action[j]((void *)ed);
			}
		}
		j++;
	}
}

void			menu_interactions(t_ed *ed, SDL_Event *e)
{
	t_context_menu	menu;
	int				i;

	tool_switch(ed, e);
	menu = ed->context_menu[ed->istates.active_tool];
	if ((ed->istates.active_tool == TL_SELECT_WALL &&
				ed->istates.active_wall == -1)
			|| (ed->istates.active_tool == TL_SELECT_THING &&
				ed->istates.active_thing == -1)
			|| (ed->istates.active_tool == TL_SELECT_SECTOR &&
				ed->istates.active_sector == -1))
		return ;
	i = 0;
	while (menu.ui_elements[i] != UIE_NONE)
	{
		if (menu.ui_elements[i] == UIE_TEXTURE_PICKER)
			texture_picker_click(ed, e, &menu);
		else if (menu.ui_elements[i] == UIE_THING_PICK)
			thing_picker(ed, e);
		else if (menu.ui_elements[i] == UIE_VARIABLE_CONTROL)
			variable_control(ed, e, &menu);
		else if (menu.ui_elements[i] == UIE_BUTTON)
			ui_button_click(ed, e, &menu);
		i++;
	}
}
