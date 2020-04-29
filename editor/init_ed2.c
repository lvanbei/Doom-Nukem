/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ed2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	init_ed5(t_ed *ed)
{
	ed->context_menu[TL_THING].ui_elements[0] = UIE_THING_PICK;
	ed->context_menu[TL_THING].ui_elements[1] = UIE_VARIABLE_CONTROL;
	ed->context_menu[TL_THING].ui_elements[2] = UIE_NONE;
	ed->context_menu[TL_THING].var_control[0] =
		&ed->istates.tl_thing_default_yaw;
	ed->context_menu[TL_THING].var_control_clamp[0][0] = -M_PI;
	ed->context_menu[TL_THING].var_control_clamp[0][1] = M_PI;
	ft_strcpy(ed->context_menu[TL_THING].var_control_strs[0], "yaw");
	ed->context_menu[TL_THING].var_control_bounds[0] = (SDL_Rect) {GRID_WIDTH
		+ 2, 160, 40, 8};
	ed->context_menu[TL_THING].num_var_controls = 1;
	ed->context_menu[TL_WALL].ui_elements[0] = UIE_TEXTURE_PICKER;
	ed->context_menu[TL_WALL].ui_elements[1] = UIE_VARIABLE_CONTROL;
	ed->context_menu[TL_WALL].ui_elements[2] = UIE_NONE;
	ed->context_menu[TL_WALL].tex_pick_p[TXP_BOT] =
		&ed->tl_w.default_b_texture;
	ed->context_menu[TL_WALL].tex_pick_p[TXP_MAIN] =
		&ed->tl_w.default_m_texture;
	ed->context_menu[TL_WALL].tex_pick_p[TXP_TOP] =
		&ed->tl_w.default_t_texture;
	ed->context_menu[TL_WALL].tex_pick_p[TXP_FLOOR] =
		&ed->tl_w.default_floor_texture;
	ed->context_menu[TL_WALL].tex_pick_p[TXP_CEIL] =
		&ed->tl_w.default_ceiling_texture;
	ed->context_menu[TL_WALL].var_control[0] = &ed->tl_w.default_floor_height;
}

void	init_ed6(t_ed *ed)
{
	ed->context_menu[TL_WALL].var_control_clamp[0][0] = MIN_FLOOR_HEIGHT;
	ed->context_menu[TL_WALL].var_control_clamp[0][1] = MAX_CEIL_HEIGHT;
	ed->context_menu[TL_WALL].var_control[1] = &ed->tl_w.default_ceiling_height;
	ed->context_menu[TL_WALL].var_control_clamp[1][0] = MIN_FLOOR_HEIGHT;
	ed->context_menu[TL_WALL].var_control_clamp[1][1] = MAX_CEIL_HEIGHT;
	ft_strcpy(ed->context_menu[TL_WALL].var_control_strs[0], "floor height");
	ed->context_menu[TL_WALL].var_control_bounds[0] = (SDL_Rect)
	{GRID_WIDTH + 2, 280, 96, 8};
	ft_strcpy(ed->context_menu[TL_WALL].var_control_strs[1], "ceiling height");
	ed->context_menu[TL_WALL].var_control_bounds[1] = (SDL_Rect)
	{GRID_WIDTH + 2, ed->context_menu[TL_WALL].var_control_bounds[0].y +
		ed->context_menu[TL_WALL].var_control_bounds[0].h + 8, 112, 8};
	ed->context_menu[TL_WALL].num_var_controls = 2;
	ed->context_menu[TL_SELECT_WALL].ui_elements[0] = UIE_TEXTURE_PICKER;
	ed->context_menu[TL_SELECT_WALL].ui_elements[1] = UIE_BUTTON;
	ed->context_menu[TL_SELECT_WALL].button_action[0] =
		&toggle_portal_active_wall;
	ed->context_menu[TL_SELECT_WALL].button_action[1] = NULL;
	ft_strcpy(ed->context_menu[TL_SELECT_WALL].button_strs[0], "toggle portal");
	ed->context_menu[TL_SELECT_WALL].button_bounds[0] = (SDL_Rect)
	{GRID_WIDTH + 2, 280, 104, 8};
	ed->context_menu[TL_SELECT_WALL].ui_elements[2] = UIE_NONE;
	ed->context_menu[TL_SELECT_SECTOR].ui_elements[0] = UIE_TEXTURE_PICKER;
	ed->context_menu[TL_SELECT_SECTOR].ui_elements[1] = UIE_VARIABLE_CONTROL;
	ed->context_menu[TL_SELECT_SECTOR].ui_elements[2] = UIE_BUTTON;
}

void	init_ed7(t_ed *ed)
{
	ed->context_menu[TL_SELECT_SECTOR].ui_elements[3] = UIE_NONE;
	ft_strcpy(ed->context_menu[TL_SELECT_SECTOR].button_strs[0],
			"delete sector");
	ed->context_menu[TL_SELECT_SECTOR].button_bounds[0] =
		(SDL_Rect) {GRID_WIDTH + 2, 320, 104, 8};
	ed->context_menu[TL_SELECT_SECTOR].button_action[0] =
		&delete_active_sector;
	ed->context_menu[TL_SELECT_SECTOR].button_action[1] = NULL;
	ed->context_menu[TL_SELECT_SECTOR].var_control_bounds[0] =
		(SDL_Rect) {GRID_WIDTH + 2, 280, 96, 8};
	ed->context_menu[TL_SELECT_SECTOR].var_control_bounds[1] =
		(SDL_Rect) {GRID_WIDTH + 2,
			ed->context_menu[TL_SELECT_SECTOR].var_control_bounds[0].y +
				ed->context_menu[TL_SELECT_SECTOR].var_control_bounds[0].h +
				8, 112, 8};
	ft_strcpy(ed->context_menu[TL_SELECT_SECTOR].var_control_strs[0],
			"floor height");
	ft_strcpy(ed->context_menu[TL_SELECT_SECTOR].var_control_strs[1],
			"ceiling height");
	ed->context_menu[TL_SELECT_SECTOR].var_control_clamp[0][0] =
		MIN_FLOOR_HEIGHT;
	ed->context_menu[TL_SELECT_SECTOR].var_control_clamp[0][1] =
		MAX_CEIL_HEIGHT;
	ed->context_menu[TL_SELECT_SECTOR].var_control_clamp[1][0] =
		MIN_FLOOR_HEIGHT;
}

void	init_ed8(t_ed *ed)
{
	ed->context_menu[TL_SELECT_SECTOR].var_control_clamp[1][1] =
		MAX_CEIL_HEIGHT;
	ed->context_menu[TL_SELECT_SECTOR].num_var_controls = 2;
	ed->context_menu[TL_SELECT_THING].ui_elements[0] = UIE_VARIABLE_CONTROL;
	ft_strcpy(ed->context_menu[TL_SELECT_THING].var_control_strs[0], "yaw");
	ed->context_menu[TL_SELECT_THING].var_control_bounds[0] = (SDL_Rect)
	{GRID_WIDTH + 2, 72, 40, 8};
	ed->context_menu[TL_SELECT_THING].num_var_controls = 1;
	ed->context_menu[TL_SELECT_THING].var_control_clamp[0][0] = -M_PI;
	ed->context_menu[TL_SELECT_THING].var_control_clamp[0][1] = M_PI;
	ed->context_menu[TL_SELECT_THING].ui_elements[1] = UIE_BUTTON;
	ed->context_menu[TL_SELECT_THING].button_action[0] = &delete_active_thing;
	ed->context_menu[TL_SELECT_THING].button_action[1] = NULL;
	ft_strcpy(ed->context_menu[TL_SELECT_THING].button_strs[0], "delete");
	ed->context_menu[TL_SELECT_THING].button_bounds[0] = (SDL_Rect)
	{GRID_WIDTH + 2, 90, 48, 8};
	ed->context_menu[TL_SELECT_THING].ui_elements[2] = UIE_NONE;
	ed->thing_height[TH_PLAYER] = PLAYER_HEIGHT;
	ed->thing_height[TH_MONSTER] = MONSTER_HEIGHT;
	ed->thing_height[TH_KEY] = KEY_HEIGHT;
	ed->thing_height[TH_JETPACK_FUEL] = JETPACK_HEIGHT;
	ed->thing_height[TH_AMMO] = AMMO_HEIGHT;
	ed->thing_height[TH_HEAL] = HEAL_HEIGHT;
	ed->thing_height[TH_RPG] = RPG_HEIGHT;
	ed->thing_height[TH_MOUSE_ENDING] = MOUSE_ENDING_HEIGHT;
}
