/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_main2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			draw_wall(t_ed *ed, int i, int color)
{
	draw_line2_clipped(ed, (t_line2f) {ed->walls[i].x, ed->walls[i].y,
			ed->walls[ed->walls[i].next_wall].x,
			ed->walls[ed->walls[i].next_wall].y},
			color);
}

void			draw_portal_arrow(t_ed *ed, int i, int color)
{
	t_draw_portal	dp;

	dp.w = (t_line2f) {ed->walls[i].x, ed->walls[i].y,
		ed->walls[ed->walls[i].next_wall].x,
		ed->walls[ed->walls[i].next_wall].y};
	dp.dx = (dp.w.x1 - dp.w.x0);
	dp.dy = (dp.w.y1 - dp.w.y0);
	dp.len = sqrt((dp.dx * dp.dx) + (dp.dy * dp.dy));
	dp.nx = -(dp.dy / dp.len);
	dp.ny = (dp.dx / dp.len);
	dp.arrow = (t_line2f) {dp.w.x0 + (dp.dx / 2.0f), dp.w.y0 + (dp.dy / 2.0f),
		(dp.w.x0 + (dp.dx / 2.0f)) + dp.nx, (dp.w.y0 + (dp.dy / 2.0f)) + dp.ny};
	draw_line2_clipped(ed, (t_line2f) {dp.arrow.x0, dp.arrow.y0, dp.arrow.x1,
			dp.arrow.y1}, color);
	dp.ang = atan2(-dp.ny, -dp.nx);
	dp.ang0 = (dp.ang - M_PI / 4);
	dp.p0_x = dp.arrow.x1 + (cos(dp.ang0));
	dp.p0_y = dp.arrow.y1 + (sin(dp.ang0));
	dp.ang1 = (dp.ang + M_PI / 4);
	dp.p1_x = dp.arrow.x1 + (cos(dp.ang1));
	dp.p1_y = dp.arrow.y1 + (sin(dp.ang1));
	draw_line2_clipped(ed, (t_line2f) {dp.arrow.x1, dp.arrow.y1, dp.p0_x,
			dp.p0_y}, color);
	draw_line2_clipped(ed, (t_line2f) {dp.arrow.x1, dp.arrow.y1, dp.p1_x,
			dp.p1_y}, color);
}

void			draw_walls(t_ed *ed)
{
	int	i;

	i = -1;
	while (++i < ed->num_walls)
		draw_wall(ed, i, (ed->walls[i].next_sector == -1) ? GREEN : RED);
}

int				point_in_view(const t_view *view, double x, double y)
{
	if (x >= view->xmin && y >= view->ymin
			&& x <= (view->xmin + view->w) && y <= (view->ymin + view->w))
		return (1);
	return (0);
}

void			draw_thing(t_ed *ed, t_draw_thing *dt, double size)
{
	if (point_in_view(&ed->view, ed->things[dt->i].x, ed->things[dt->i].y))
	{
		map_to_screen(&ed->view, (t_v2f) {ed->things[dt->i].x,
				ed->things[dt->i].y}, &dt->fx, &dt->fy);
		dt->x = dt->fx;
		dt->y = dt->fy;
		dt->w = ed->ed_textures[ed->things[dt->i].type]->w;
		dt->h = ed->ed_textures[ed->things[dt->i].type]->h;
		dt->ratio = size / dt->w;
		dt->w = dt->w * dt->ratio * dt->scale;
		dt->h = dt->h * dt->ratio * dt->scale;
		dt->rect = (SDL_Rect) {dt->x - (dt->w / 2), dt->y - (dt->h / 2),
			dt->w, dt->h};
		SDL_BlitScaled(ed->ed_textures[ed->things[dt->i].type], NULL,
				ed->surface, &dt->rect);
	}
}
