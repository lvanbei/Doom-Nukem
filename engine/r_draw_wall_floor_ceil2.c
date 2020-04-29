/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_wall_floor_ceil2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_v2f				screen_to_worldspace(int i, int j,
		const t_plane_info *info)
{
	t_v3f	p;
	t_v2f	w;

	p.z = info->z;
	p.y = (p.z * -VSCALE) / ((double)(j - HEIGHT_CENTER - info->pitch_shift));
	p.x = ((i - WIDTH_CENTER) * p.y) / (double)HSCALE;
	w.x = p.x * info->rev_cos_ang - p.y * info->rev_sin_ang;
	w.y = p.x * info->rev_sin_ang + p.y * info->rev_cos_ang;
	w.x += info->player_x;
	w.y += info->player_y;
	return (w);
}

static inline void	init_draw_hline(t_draw_line *dl, t_draw_line_local *dll)
{
	dll->p0 = screen_to_worldspace(dl->x0, dl->y, dl->info);
	dll->p1 = screen_to_worldspace(dl->x1, dl->y, dl->info);
	dll->delta_x = dll->p1.x - dll->p0.x;
	dll->delta_y = dll->p1.y - dll->p0.y;
	dll->delta_x *= dl->texture->w;
	dll->delta_y *= dl->texture->h;
	dll->delta_x /= dll->count;
	dll->delta_y /= dll->count;
}

static inline void	draw_hline_loop(t_draw_line *dl, t_draw_line_local *dll)
{
	if (dll->x0_tex_offset < 0.0f)
		dll->x0_tex_offset += dl->texture->w;
	if (dll->x0_tex_offset >= dl->texture->w)
		dll->x0_tex_offset -= dl->texture->w;
	if (dll->y0_tex_offset < 0.0f)
		dll->y0_tex_offset += dl->texture->h;
	if (dll->y0_tex_offset >= dl->texture->h)
		dll->y0_tex_offset -= dl->texture->h;
	*(dll->dest) = ((uint32_t *)dl->texture->pixels)[((int)dll->x0_tex_offset)
		+ dl->texture->w * ((int)dll->y0_tex_offset)];
	dll->x0_tex_offset += dll->delta_x;
	dll->y0_tex_offset += dll->delta_y;
	dll->dest++;
}

void				draw_hline(t_draw_line dl)
{
	t_draw_line_local dll;

	dll.count = dl.x1 - dl.x0 + 1;
	if (dll.count < 0 || (dl.y == (HEIGHT_CENTER + dl.info->pitch_shift)))
		return ;
	init_draw_hline(&dl, &dll);
	if (dll.p0.x < 0)
		dll.x0_tex_offset = -(floor(dll.p0.x) - dll.p0.x);
	else
		dll.x0_tex_offset = dll.p0.x - floor(dll.p0.x);
	if (dll.p0.y < 0)
		dll.y0_tex_offset = -(floor(dll.p0.y) - dll.p0.y);
	else
		dll.y0_tex_offset = dll.p0.y - floor(dll.p0.y);
	dll.x0_tex_offset *= dl.texture->w;
	dll.y0_tex_offset *= dl.texture->h;
	dll.dest = &(((uint32_t *)dl.r->eng->surface->pixels)[dl.x0 + WIN_WIDTH
			* dl.y]);
	while (dll.count--)
		draw_hline_loop(&dl, &dll);
}
