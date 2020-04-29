/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_portal_flats.c                              :+:      :+:    :+:   */
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

static inline void		draw_portal_flats1(t_pvwall *pvwall,
		t_draw_info *d, t_draw_portal *dp)
{
	dp->t_u1 = (dp->wall_len * dp->t_texture->w);
	dp->b_u1 = (dp->wall_len * dp->b_texture->w);
	dp->t_u_range = dp->t_u1 - dp->t_u0;
	dp->b_u_range = dp->b_u1 - dp->b_u0;
	if (pvwall->flags & PV_CLIPPED0)
	{
		dp->wp_pl = line_len(dp->w.x0, dp->w.y0, pvwall->screenspace.x0,
				pvwall->screenspace.y0);
		dp->t_u0 = (dp->wp_pl / dp->wall_len) * dp->t_u_range;
		dp->b_u0 = (dp->wp_pl / dp->wall_len) * dp->b_u_range;
	}
	if (pvwall->flags & PV_CLIPPED1)
	{
		dp->wp_pl = line_len(dp->w.x0, dp->w.y0, pvwall->screenspace.x1,
				pvwall->screenspace.y1);
		dp->t_u1 = (dp->wp_pl / dp->wall_len) * dp->t_u_range;
		dp->b_u1 = (dp->wp_pl / dp->wall_len) * dp->b_u_range;
	}
	dp->t_u0_z0 = dp->t_u0 / pvwall->dist0;
	dp->t_u1_z1 = dp->t_u1 / pvwall->dist1;
	dp->b_u0_z0 = dp->b_u0 / pvwall->dist0;
	dp->b_u1_z1 = dp->b_u1 / pvwall->dist1;
	dp->f1_z0 = 1.0f / pvwall->dist0;
	dp->f1_z1 = 1.0f / pvwall->dist1;
	dp->count = d->first - pvwall->col0;
}

static inline void		draw_portal_flats2(t_render *r, t_draw_info *d,
		t_draw_portal *dp, int i)
{
	dp->top_yh = d->top_yh_frac;
	dp->bot_yl = d->bot_yl_frac;
	dp->bot_yh = d->bot_yh_frac;
	if (dp->top_yl < r->umost[i])
	{
		dp->t_v = (r->umost[i] - dp->top_yl) * dp->t_vstep;
		dp->top_yl = r->umost[i];
	}
	else if (dp->top_yl > r->dmost[i])
		dp->top_yl = r->dmost[i];
	if (dp->top_yh < dp->top_yl)
		dp->top_yh = dp->top_yl;
	else if (dp->top_yh > r->dmost[i])
		dp->top_yh = r->dmost[i];
	if (dp->bot_yl < dp->top_yh)
	{
		dp->b_v = (dp->top_yh - dp->bot_yl) * dp->b_vstep;
		dp->bot_yl = dp->top_yh;
	}
	else if (dp->bot_yl > r->dmost[i])
		dp->bot_yl = r->dmost[i];
	if (dp->bot_yh < dp->bot_yl)
		dp->bot_yh = dp->bot_yl;
	else if (dp->bot_yh > r->dmost[i])
		dp->bot_yh = r->dmost[i];
}

static inline void		draw_portal_flats3(t_render *r, t_draw_info *d,
		t_draw_portal *dp, int i)
{
	dp->alpha = dp->count / d->s_wall_width;
	dp->t_u = (((1 - dp->alpha) * dp->t_u0_z0) + (dp->alpha * dp->t_u1_z1)) /
		(((1 - dp->alpha) * dp->f1_z0) + (dp->alpha * dp->f1_z1));
	dp->b_u = (((1 - dp->alpha) * dp->b_u0_z0) + (dp->alpha * dp->b_u1_z1)) /
		(((1 - dp->alpha) * dp->f1_z0) + (dp->alpha * dp->f1_z1));
	draw_col(r->eng->surface, (t_draw_col) {i, dp->top_yl, dp->top_yh,
			dp->t_texture, dp->t_u, dp->t_v, dp->t_vstep});
	draw_col(r->eng->surface, (t_draw_col) {i, dp->bot_yl, dp->bot_yh,
			dp->b_texture, dp->b_u, dp->b_v, dp->b_vstep});
	d->upwb[i] = (short)dp->top_yl;
	d->tmp_umost[i] = (short)dp->top_yh;
	d->tmp_dmost[i] = (short)dp->bot_yl;
	d->dwb[i] = (short)dp->bot_yh;
	d->top_yl_frac += d->top_yl_step;
	d->top_yh_frac += d->top_yh_step;
	d->bot_yl_frac += d->bot_yl_step;
	d->bot_yh_frac += d->bot_yh_step;
	dp->count += 1;
}

void					draw_portal_flats(t_render *r, t_pvwall *pvwall,
		t_draw_info *d)
{
	t_draw_portal	dp;
	int				i;

	dp.wall = r->eng->walls[pvwall->wall_id];
	dp.t_texture = r->eng->textures[dp.wall.t_texture];
	dp.b_texture = r->eng->textures[dp.wall.b_texture];
	dp.w = pvwall->playerspace;
	dp.wall_len = line_len(dp.w.x0, dp.w.y0, dp.w.x1, dp.w.y1);
	dp.t_u0 = 0;
	dp.b_u0 = 0;
	draw_portal_flats1(pvwall, d, &dp);
	i = d->first - 1;
	while (++i <= d->last)
	{
		dp.t_v = 0;
		dp.b_v = 0;
		dp.t_vstep = (d->top_height * dp.t_texture->h) /
			(d->top_yh_frac - d->top_yl_frac);
		dp.b_vstep = (d->bot_height * dp.b_texture->h) /
			(d->bot_yh_frac - d->bot_yl_frac);
		dp.top_yl = d->top_yl_frac;
		draw_portal_flats2(r, d, &dp, i);
		draw_portal_flats3(r, d, &dp, i);
	}
}
