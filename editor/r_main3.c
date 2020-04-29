/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_main3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_things(t_ed *ed)
{
	t_draw_thing			dt;
	static const double		default_size[TH_VISIBLE_END] =
	{22.0f, 25.0f, 30.0f, 30.0f, 32.0f, 22.0f, 30.0f, 30.0f};

	dt.player = ed->player;
	dt.scale = 30.0f / (ed->view.w);
	if (ed->player_set && point_in_view(&ed->view, ed->player.x, ed->player.y))
	{
		map_to_screen(&ed->view, (t_v2f) {dt.player.x, dt.player.y},
				&dt.fx, &dt.fy);
		dt.x = dt.fx;
		dt.y = dt.fy;
		dt.w = ed->ed_textures[UI_PLAYER]->w;
		dt.h = ed->ed_textures[UI_PLAYER]->h;
		dt.ratio = default_size[TH_PLAYER] / dt.w;
		dt.w = dt.w * dt.ratio * dt.scale;
		dt.h = dt.h * dt.ratio * dt.scale;
		dt.rect = (SDL_Rect){dt.x - (dt.w / 2), dt.y - (dt.h / 2), dt.w, dt.h};
		SDL_BlitScaled(ed->ed_textures[UI_PLAYER], NULL, ed->surface, &dt.rect);
	}
	dt.i = -1;
	while (++dt.i < ed->num_things)
		draw_thing(ed, &dt, default_size[ed->things[dt.i].type]);
}

void	draw_tl_w(t_ed *ed)
{
	int		i;
	int		end_wall;
	double	p_x;
	double	p_y;

	if (ed->tl_w.num_walls > 1)
	{
		end_wall = ed->num_walls + ed->tl_w.num_walls - 1;
		i = ed->num_walls - 1;
		while (++i < end_wall)
			draw_wall(ed, i, BLUE);
	}
	else
		i = ed->num_walls;
	if (ed->tl_w.num_walls)
	{
		screen_to_map(&ed->view, (t_v2) {ed->istates.mouse_x,
				ed->istates.mouse_y}, &p_x, &p_y);
		draw_line2_clipped(ed, (t_line2f) {ed->walls[i].x,
				ed->walls[i].y, p_x, p_y}, YELLOW);
	}
}
