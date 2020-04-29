/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_door_flats.c                                :+:      :+:    :+:   */
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

static inline void		draw_door_flats_loop0(t_draw_info *d,
		t_draw_door *dd)
{
	dd->t_v = 0;
	dd->m_v = 0;
	dd->b_v = 0;
	dd->t_vstep = (d->top_height * dd->t_texture->h) /
		(d->top_yh_frac - d->top_yl_frac);
	dd->m_vstep = (dd->wall_height * dd->m_texture->h) /
		(d->bot_yl_frac - d->top_yh_frac);
	dd->b_vstep = (d->bot_height * dd->b_texture->h) /
		(d->bot_yh_frac - d->bot_yl_frac);
}

static inline void		draw_door_flats_loop1(t_render *r, t_draw_info *d,
		t_draw_door *dd, int i)
{
	dd->top_yl = d->top_yl_frac;
	dd->top_yh = d->top_yh_frac;
	dd->mid = d->mid_frac;
	dd->bot_yl = d->bot_yl_frac;
	dd->bot_yh = d->bot_yh_frac;
	if (dd->top_yl < r->umost[i])
	{
		dd->t_v = (r->umost[i] - dd->top_yl) * dd->t_vstep;
		dd->top_yl = r->umost[i];
	}
	else if (dd->top_yl > r->dmost[i])
		dd->top_yl = r->dmost[i];
	if (dd->top_yh < dd->top_yl)
	{
		dd->m_v = (dd->top_yl - dd->top_yh) * dd->m_vstep;
		dd->top_yh = dd->top_yl;
	}
	else if (dd->top_yh > r->dmost[i])
		dd->top_yh = r->dmost[i];
	if (dd->mid < dd->top_yh)
		dd->mid = dd->top_yh;
	else if (dd->mid > r->dmost[i])
		dd->mid = r->dmost[i];
}

static inline void		draw_door_flats_loop2(t_render *r, t_draw_info *d,
		t_draw_door *dd, int i)
{
	if (dd->bot_yl < dd->top_yh)
	{
		dd->b_v = (dd->top_yh - dd->bot_yl) * dd->b_vstep;
		dd->bot_yl = dd->top_yh;
	}
	else if (dd->bot_yl > r->dmost[i])
		dd->bot_yl = r->dmost[i];
	if (dd->bot_yh < dd->bot_yl)
		dd->bot_yh = dd->bot_yl;
	else if (dd->bot_yh > r->dmost[i])
		dd->bot_yh = r->dmost[i];
	dd->alpha = dd->count / d->s_wall_width;
	dd->t_u = (((1 - dd->alpha) * dd->t_u0_z0) + (dd->alpha * dd->t_u1_z1))
		/ (((1 - dd->alpha) * dd->f1_z0) + (dd->alpha * dd->f1_z1));
	dd->m_u = (((1 - dd->alpha) * dd->m_u0_z0) + (dd->alpha * dd->m_u1_z1))
		/ (((1 - dd->alpha) * dd->f1_z0) + (dd->alpha * dd->f1_z1));
	dd->b_u = (((1 - dd->alpha) * dd->b_u0_z0) + (dd->alpha * dd->b_u1_z1))
		/ (((1 - dd->alpha) * dd->f1_z0) + (dd->alpha * dd->f1_z1));
	draw_col(r->eng->surface, (t_draw_col) {i, dd->top_yl, dd->top_yh,
			dd->t_texture, dd->t_u, dd->t_v, dd->t_vstep});
	draw_col(r->eng->surface, (t_draw_col) {i, dd->top_yh, dd->mid,
			dd->m_texture, dd->m_u, dd->m_v, dd->m_vstep});
	draw_col(r->eng->surface, (t_draw_col) {i, dd->bot_yl, dd->bot_yh,
			dd->b_texture, dd->b_u, dd->b_v, dd->b_vstep});
	d->upwb[i] = (short)dd->top_yl;
}

void					draw_door_flats(t_render *r, t_pvwall *pvwall,
		t_draw_info *d)
{
	t_draw_door		dd;
	int				i;

	draw_door_flats0(r, pvwall, &dd);
	draw_door_flats1(d, pvwall, &dd);
	dd.wall_height = r->eng->sectors[pvwall->sect_id].ceiling_height -
		r->eng->sectors[pvwall->sect_id].floor_height;
	i = d->first - 1;
	while (++i <= d->last)
	{
		draw_door_flats_loop0(d, &dd);
		draw_door_flats_loop1(r, d, &dd, i);
		draw_door_flats_loop2(r, d, &dd, i);
		d->tmp_umost[i] = (short)dd.mid;
		d->tmp_dmost[i] = (short)dd.bot_yl;
		d->dwb[i] = (short)dd.bot_yh;
		d->top_yl_frac += d->top_yl_step;
		d->top_yh_frac += d->top_yh_step;
		d->mid_frac += d->mid_step;
		d->bot_yl_frac += d->bot_yl_step;
		d->bot_yh_frac += d->bot_yh_step;
		dd.count += 1;
	}
}
