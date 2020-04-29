/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_wall_flats.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void				draw_col(SDL_Surface *screen, t_draw_col dc)
{
	uint32_t	*dest;
	int			count;

	count = dc.yh - dc.yl;
	if (count < 0)
		return ;
	dest = &(((uint32_t *)screen->pixels)[dc.x + WIN_WIDTH * dc.yl]);
	while (count--)
	{
		*dest = ((uint32_t *)dc.texture->pixels)[(dc.u % dc.texture->w) +
			dc.texture->w * ((int)(dc.v) % dc.texture->h)];
		dest += WIN_WIDTH;
		dc.v += dc.v_step;
	}
}

static inline void		draw_wall_flats_init(t_render *r, t_pvwall *pvwall,
		t_draw_wall *dw)
{
	dw->wall = r->eng->walls[pvwall->wall_id];
	dw->m_texture = r->eng->textures[dw->wall.m_texture];
	dw->w = pvwall->playerspace;
	dw->wall_len = line_len(dw->w.x0, dw->w.y0, dw->w.x1, dw->w.y1);
	dw->m_u0 = 0;
	dw->m_u1 = (dw->wall_len * dw->m_texture->w);
	dw->m_u_range = dw->m_u1 - dw->m_u0;
	if (pvwall->flags & PV_CLIPPED0)
	{
		dw->wp_pl = line_len(dw->w.x0, dw->w.y0, pvwall->screenspace.x0,
				pvwall->screenspace.y0);
		dw->m_u0 = (dw->wp_pl / dw->wall_len) * dw->m_u_range;
	}
	if (pvwall->flags & PV_CLIPPED1)
	{
		dw->wp_pl = line_len(dw->w.x0, dw->w.y0, pvwall->screenspace.x1,
				pvwall->screenspace.y1);
		dw->m_u1 = (dw->wp_pl / dw->wall_len) * dw->m_u_range;
	}
	dw->m_u0_z0 = dw->m_u0 / pvwall->dist0;
	dw->m_u1_z1 = dw->m_u1 / pvwall->dist1;
	dw->f1_z0 = 1.0f / pvwall->dist0;
	dw->f1_z1 = 1.0f / pvwall->dist1;
	dw->wall_height = r->eng->sectors[pvwall->sect_id].ceiling_height -
		r->eng->sectors[pvwall->sect_id].floor_height;
}

static inline void		draw_wall_flats_loopsub(t_render *r, t_draw_info *d,
		t_draw_wall *dw, int i)
{
	dw->m_v = 0;
	dw->m_vstep = (dw->wall_height * dw->m_texture->h) /
		(d->bot_yl_frac - d->top_yh_frac);
	dw->top_yh = d->top_yh_frac;
	dw->bot_yl = d->bot_yl_frac;
	if (dw->top_yh < r->umost[i])
	{
		dw->m_v = (r->umost[i] - dw->top_yh) * dw->m_vstep;
		dw->top_yh = r->umost[i];
	}
	else if (dw->top_yh > r->dmost[i])
		dw->top_yh = r->dmost[i];
	if (dw->bot_yl < dw->top_yh)
		dw->bot_yl = dw->top_yh;
	else if (dw->bot_yl > r->dmost[i])
		dw->bot_yl = r->dmost[i];
	dw->alpha = dw->count / d->s_wall_width;
}

void					draw_wall_flats(t_render *r, t_pvwall *pvwall,
		t_draw_info *d)
{
	t_draw_wall	dw;
	int			i;

	draw_wall_flats_init(r, pvwall, &dw);
	dw.count = d->first - pvwall->col0;
	i = d->first - 1;
	while (++i <= d->last)
	{
		draw_wall_flats_loopsub(r, d, &dw, i);
		dw.m_u = (((1 - dw.alpha) * dw.m_u0_z0) + (dw.alpha * dw.m_u1_z1)) /
			(((1 - dw.alpha) * dw.f1_z0) + (dw.alpha * dw.f1_z1));
		draw_col(r->eng->surface, (t_draw_col) {i, dw.top_yh, dw.bot_yl,
				dw.m_texture, dw.m_u, dw.m_v, dw.m_vstep});
		d->upwb[i] = (short)dw.top_yh;
		d->dwb[i] = (short)dw.bot_yl;
		d->top_yh_frac += d->top_yh_step;
		d->bot_yl_frac += d->bot_yl_step;
		dw.count += 1;
	}
}
