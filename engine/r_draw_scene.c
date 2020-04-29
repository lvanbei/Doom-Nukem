/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline void		update_angle(t_render *r)
{
	double	angle;
	double	rev_angle;

	angle = 0;
	rev_angle = 0;
	if (r->eng->player.attr.yaw != r->prev_yaw)
	{
		angle = (M_PI / 2 - r->eng->player.attr.yaw);
		r->eng->sin_ang = sin(angle);
		r->eng->cos_ang = cos(angle);
		rev_angle = -angle;
		r->eng->rev_sin_ang = sin(rev_angle);
		r->eng->rev_cos_ang = cos(rev_angle);
		r->prev_yaw = r->eng->player.attr.yaw;
	}
}

static inline void		ds_loop0(t_render *r, t_draw_scene *ds)
{
	ds->nearest_bunch = 0;
	ds->bunch_hits[ds->nearest_bunch] = 1;
	ds->i = 0;
	while (++(ds->i) < ds->num_bunches)
	{
		if ((ds->j = bunch_front(r, ds->i, ds->nearest_bunch)) < 0)
			continue ;
		ds->bunch_hits[ds->i] = 1;
		if (ds->j == 1)
		{
			slow_bzero(ds->bunch_hits, sizeof(ds->bunch_hits));
			ds->bunch_hits[ds->nearest_bunch] = 1;
			ds->nearest_bunch = ds->i;
		}
	}
}

static inline void		ds_loop1(t_render *r, t_draw_scene *ds)
{
	ds->i = -1;
	while (++(ds->i) < ds->num_bunches)
	{
		if (ds->bunch_hits[ds->i])
			continue ;
		if ((ds->j = bunch_front(r, ds->i, ds->nearest_bunch)) < 0)
			continue ;
		ds->bunch_hits[ds->i] = 1;
		if (ds->j == 1)
		{
			ds->bunch_hits[ds->nearest_bunch] = 1;
			ds->nearest_bunch = ds->i;
			ds->i = 0;
		}
	}
}

void					draw_scene(t_render *r)
{
	t_draw_scene ds;

	update_angle(r);
	r->clip.num_smost = 0;
	r->clip.num_smost_walls = 0;
	r->full_cols = WIN_WIDTH;
	slow_bzero(r->umost, sizeof(r->umost));
	ds.i = -1;
	while (++ds.i < WIN_WIDTH)
		r->dmost[ds.i] = WIN_HEIGHT - 1;
	slow_bzero(ds.bunch_hits, sizeof(ds.bunch_hits));
	ds.num_bunches = r->num_bunches;
	while (ds.num_bunches && r->full_cols)
	{
		ds_loop0(r, &ds);
		ds_loop1(r, &ds);
		ds.w = r->bunches[ds.nearest_bunch].first_idx;
		while (ds.w <= r->bunches[ds.nearest_bunch].last_idx)
			draw_pvwall(r, ds.w++);
		ds.num_bunches--;
		r->bunches[ds.nearest_bunch] = r->bunches[ds.num_bunches];
	}
}
