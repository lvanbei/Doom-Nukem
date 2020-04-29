/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_door_flats2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void		draw_door_flats0(t_render *r, t_pvwall *pvwall, t_draw_door *dd)
{
	dd->wall = r->eng->walls[pvwall->wall_id];
	dd->t_texture = r->eng->textures[dd->wall.t_texture];
	if (dd->wall.m_texture == -1)
		dd->m_texture = r->eng->textures[3];
	else
		dd->m_texture = r->eng->textures[dd->wall.m_texture];
	dd->b_texture = r->eng->textures[dd->wall.b_texture];
	dd->w = pvwall->playerspace;
	dd->wall_len = line_len(dd->w.x0, dd->w.y0, dd->w.x1, dd->w.y1);
	dd->t_u0 = 0;
	dd->m_u0 = 0;
	dd->b_u0 = 0;
	dd->t_u1 = (dd->wall_len * dd->t_texture->w);
	dd->m_u1 = (dd->wall_len * dd->m_texture->w);
	dd->b_u1 = (dd->wall_len * dd->b_texture->w);
	dd->t_u_range = dd->t_u1 - dd->t_u0;
	dd->m_u_range = dd->m_u1 - dd->m_u0;
	dd->b_u_range = dd->b_u1 - dd->b_u0;
}

void		draw_door_flats1(t_draw_info *d, t_pvwall *pvwall, t_draw_door *dd)
{
	if (pvwall->flags & PV_CLIPPED0)
	{
		dd->wp_pl = line_len(dd->w.x0, dd->w.y0, pvwall->screenspace.x0,
				pvwall->screenspace.y0);
		dd->t_u0 = (dd->wp_pl / dd->wall_len) * dd->t_u_range;
		dd->m_u0 = (dd->wp_pl / dd->wall_len) * dd->m_u_range;
		dd->b_u0 = (dd->wp_pl / dd->wall_len) * dd->b_u_range;
	}
	if (pvwall->flags & PV_CLIPPED1)
	{
		dd->wp_pl = line_len(dd->w.x0, dd->w.y0, pvwall->screenspace.x1,
				pvwall->screenspace.y1);
		dd->t_u1 = (dd->wp_pl / dd->wall_len) * dd->t_u_range;
		dd->m_u1 = (dd->wp_pl / dd->wall_len) * dd->m_u_range;
		dd->b_u1 = (dd->wp_pl / dd->wall_len) * dd->b_u_range;
	}
	dd->t_u0_z0 = dd->t_u0 / pvwall->dist0;
	dd->t_u1_z1 = dd->t_u1 / pvwall->dist1;
	dd->m_u0_z0 = dd->m_u0 / pvwall->dist0;
	dd->m_u1_z1 = dd->m_u1 / pvwall->dist1;
	dd->b_u0_z0 = dd->b_u0 / pvwall->dist0;
	dd->b_u1_z1 = dd->b_u1 / pvwall->dist1;
	dd->f1_z0 = 1.0f / pvwall->dist0;
	dd->f1_z1 = 1.0f / pvwall->dist1;
	dd->count = d->first - pvwall->col0;
}
