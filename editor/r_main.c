/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			draw_tl_select_wall(t_ed *ed)
{
	if (ed->istates.hot_wall != -1)
		draw_wall(ed, ed->istates.hot_wall, WHITE);
	if (ed->istates.active_wall != -1)
	{
		draw_wall(ed, ed->istates.active_wall, CYAN);
		if (ed->istates.active_wall_has_co)
			draw_portal_arrow(ed, ed->istates.active_wall,
					(ed->walls[ed->istates.active_wall].next_sector != -1)
					? RED : CYAN);
		print_to_screen(ed->surface, (t_text) { &ed->font_table, 0, 20,
				YELLOW}, "active wall: %d", ed->istates.active_wall);
	}
}

void			draw_tl_select_sector(t_ed *ed)
{
	int	i;

	if (ed->istates.hot_sector >= 0)
	{
		i = ed->sectors[ed->istates.hot_sector].start_wall - 1;
		while (++i < ed->sectors[ed->istates.hot_sector].start_wall +
				ed->sectors[ed->istates.hot_sector].num_walls)
			draw_wall(ed, i, WHITE);
	}
	if (ed->istates.active_sector >= 0)
	{
		print_to_screen(ed->surface, (t_text) { &ed->font_table, 0, 20,
				YELLOW}, "active sector: %d", ed->istates.active_sector);
		i = ed->sectors[ed->istates.active_sector].start_wall - 1;
		while (++i < ed->sectors[ed->istates.active_sector].start_wall +
				ed->sectors[ed->istates.active_sector].num_walls)
		{
			draw_wall(ed, i, CYAN);
		}
	}
}

void			draw_tl_select_thing(t_ed *ed)
{
	if (ed->istates.active_thing >= 0)
		print_to_screen(ed->surface, (t_text) { &ed->font_table, 0, 20,
				YELLOW}, "active thing: %d", ed->istates.active_thing);
	else if (ed->istates.active_thing == -2)
		print_to_screen(ed->surface, (t_text) { &ed->font_table, 0, 20,
				YELLOW}, "active thing: player");
}

void			render(t_ed *ed)
{
	slow_bzero(ed->surface->pixels, WIN_WIDTH * WIN_HEIGHT * 4);
	draw_grid(ed->surface, &ed->view);
	draw_walls(ed);
	print_to_screen(ed->surface, (t_text) { &ed->font_table, 0, 0, WHITE},
			"xmin: %f, ymin: %f", ed->view.xmin, ed->view.ymin);
	print_to_screen(ed->surface, (t_text) { &ed->font_table, 0, 10, WHITE},
			"dx: %f dx^-1: %f", ed->view.dx, ed->view.dx_1);
	draw_menu(ed);
	if (ed->istates.active_tool == TL_WALL)
		draw_tl_w(ed);
	else if (ed->istates.active_tool == TL_SELECT_WALL)
		draw_tl_select_wall(ed);
	else if (ed->istates.active_tool == TL_SELECT_SECTOR)
		draw_tl_select_sector(ed);
	else if (ed->istates.active_tool == TL_SELECT_THING)
		draw_tl_select_thing(ed);
	draw_things(ed);
	SDL_UpdateWindowSurface(ed->window);
}
