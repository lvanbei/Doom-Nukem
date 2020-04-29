/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			draw_texture_picker2(t_ed *ed, const t_context_menu *menu,
		int colors[5])
{
	int	i;

	i = -1;
	while (++i < TXP_END)
		print_to_screen(ed->surface, (t_text) {&ed->font_table,
				ed->tex_pick_strsbounds[i].x, ed->tex_pick_strsbounds[i].y,
				colors[i]}, "%s", ed->tex_pick_strs[i]);
	i = -1;
	while (++i < NUM_TEXTURES)
		if (SDL_BlitScaled(ed->textures[i], NULL,
					ed->surface, &ed->texture_pickbounds[i + 1]) != 0)
			abort_error(ed, "i: %d %s\n", i, SDL_GetError());
	if (ed->istates.txp_hot_texture != -1)
		draw_rect(ed->surface,
				&ed->texture_pickbounds[ed->istates.txp_hot_texture], GREEN);
	draw_rect(ed->surface,
			&ed->texture_pickbounds[
			*(menu->tex_pick_p[ed->tl_w.active_tex_pick]) + 1], YELLOW);
}

static void		draw_texture_picker(t_ed *ed, const t_context_menu *menu)
{
	int	colors[5];

	slow_memset(colors, 0xFF, 5 * sizeof(int));
	if (ed->tl_w.hot_tex_pick != TXP_NONE)
		colors[ed->tl_w.hot_tex_pick] = GREEN;
	colors[ed->tl_w.active_tex_pick] = YELLOW;
	if (ed->istates.active_tool == TL_SELECT_WALL)
	{
		colors[3] = DIMGRAY;
		colors[4] = DIMGRAY;
	}
	if (ed->istates.active_tool == TL_SELECT_SECTOR)
	{
		colors[0] = DIMGRAY;
		colors[1] = DIMGRAY;
		colors[2] = DIMGRAY;
	}
	draw_texture_picker2(ed, menu, colors);
}

static void		draw_var_controllers(t_ed *ed, const t_context_menu *menu)
{
	int	i;
	int	colors[MAX_VAR_CONTROLS];

	slow_memset(colors, 0xFF, 5 * sizeof(int));
	if (ed->istates.active_slider != -1)
		colors[ed->istates.active_slider] = YELLOW;
	i = (ed->things[ed->istates.active_thing].type == TH_MONSTER) ? 0 : -1;
	while (++i < menu->num_var_controls)
	{
		print_to_screen(ed->surface, (t_text) {&ed->font_table,
				menu->var_control_bounds[i].x, menu->var_control_bounds[i].y,
				colors[i]},
				"%s: %f", menu->var_control_strs[i], *(menu->var_control[i]));
	}
}

static void		draw_buttons(t_ed *ed, const t_context_menu *menu)
{
	int i;

	i = 0;
	while (menu->button_action[i] != NULL)
	{
		print_to_screen(ed->surface, (t_text) {&ed->font_table,
				menu->button_bounds[i].x, menu->button_bounds[i].y, WHITE},
				"%s", menu->button_strs[i]);
		i++;
	}
}

void			draw_menu(t_ed *ed)
{
	t_context_menu	menu;
	int				i;

	draw_menu_tool(ed);
	menu = ed->context_menu[ed->istates.active_tool];
	if ((ed->istates.active_tool == TL_SELECT_WALL
				&& ed->istates.active_wall == -1)
			|| (ed->istates.active_tool == TL_SELECT_SECTOR
				&& ed->istates.active_sector == -1)
			|| (ed->istates.active_tool == TL_SELECT_THING
				&& ed->istates.active_thing == -1))
		return ;
	i = 0;
	while (menu.ui_elements[i] != UIE_NONE)
	{
		if (menu.ui_elements[i] == UIE_TEXTURE_PICKER)
			draw_texture_picker(ed, &menu);
		else if (menu.ui_elements[i] == UIE_VARIABLE_CONTROL)
			draw_var_controllers(ed, &menu);
		else if (menu.ui_elements[i] == UIE_BUTTON)
			draw_buttons(ed, &menu);
		else if (menu.ui_elements[i] == UIE_THING_PICK)
			draw_thing_types(ed);
		i++;
	}
}
