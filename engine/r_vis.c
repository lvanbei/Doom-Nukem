/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_vis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:22:14 by hde-moff          #+#    #+#             */
/*   Updated: 2020/01/28 10:22:15 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int					sprite_wall_front(const t_render *r, int sprite_num,
		int pvwall_num)
{
	t_v2f		p;
	t_line2f	seg;
	double		cross;

	p = r->pvsprites[sprite_num].p;
	seg = r->pvwalls[pvwall_num].playerspace;
	cross = cross_product(seg.x1 - seg.x0, seg.y1 - seg.y0, p.x - seg.x0,
			p.y - seg.y0);
	return (cross >= 0);
}

static inline int	wall_front0(t_wall_front *wf)
{
	wf->w_vx = wf->w1.x1 - wf->w1.x0;
	wf->w_vy = wf->w1.y1 - wf->w1.y0;
	wf->cross_start = cross_product(wf->w_vx, wf->w_vy, wf->w2.x0 - wf->w1.x0,
			wf->w2.y0 - wf->w1.y0);
	wf->cross_end = cross_product(wf->w_vx, wf->w_vy, wf->w2.x1 - wf->w1.x0,
			wf->w2.y1 - wf->w1.y0);
	if (wf->cross_start == 0.0f)
	{
		wf->cross_start = wf->cross_end;
		if (wf->cross_start == 0.0f)
			return (-1);
	}
	if (wf->cross_end == 0.0f)
		wf->cross_end = wf->cross_start;
	if (sign(wf->cross_start) == sign(wf->cross_end))
	{
		wf->cross_origin = cross_product(wf->w_vx, wf->w_vy, -wf->w1.x0,
				-wf->w1.y0);
		if (sign(wf->cross_start) != sign(wf->cross_origin))
			return (1);
		return (0);
	}
	return (-2);
}

static inline int	wall_front1(t_wall_front *wf)
{
	wf->w_vx = wf->w2.x1 - wf->w2.x0;
	wf->w_vy = wf->w2.y1 - wf->w2.y0;
	wf->cross_start = cross_product(wf->w_vx, wf->w_vy, wf->w1.x0 - wf->w2.x0,
			wf->w1.y0
			- wf->w2.y0);
	wf->cross_end = cross_product(wf->w_vx, wf->w_vy, wf->w1.x1 - wf->w2.x0,
			wf->w1.y1
			- wf->w2.y0);
	if (wf->cross_start == 0.0f)
	{
		wf->cross_start = wf->cross_end;
		if (wf->cross_start == 0.0f)
			return (-1);
	}
	if (wf->cross_end == 0.0f)
		wf->cross_end = wf->cross_start;
	if (sign(wf->cross_start) == sign(wf->cross_end))
	{
		wf->cross_origin = cross_product(wf->w_vx, wf->w_vy, -wf->w2.x0,
				-wf->w2.y0);
		if (sign(wf->cross_start) == sign(wf->cross_origin))
			return (1);
		return (0);
	}
	return (-2);
}

static int			wall_front(const t_render *r, int i1, int i2)
{
	t_wall_front	wf;
	int				ret;

	wf.w1 = r->pvwalls[i1].playerspace;
	wf.w2 = r->pvwalls[i2].playerspace;
	ret = wall_front0(&wf);
	if (ret != -2)
		return (ret);
	ret = wall_front1(&wf);
	if (ret != -2)
		return (ret);
	return (-2);
}

int					bunch_front(const t_render *r, int bunch1, int bunch2)
{
	t_bunch_front bf;

	bf.b1_firstx = r->bunches[bunch1].firstx;
	bf.b2_lastx = r->bunches[bunch2].lastx;
	if (bf.b2_lastx < bf.b1_firstx)
		return (-1);
	bf.b1_lastx = r->bunches[bunch1].lastx;
	bf.b2_firstx = r->bunches[bunch2].firstx;
	if (bf.b1_lastx < bf.b2_firstx)
		return (-1);
	if (bf.b2_firstx < bf.b1_firstx)
	{
		bf.intersect_idx = r->bunches[bunch2].first_idx;
		while (r->pvwalls[bf.intersect_idx].col1 < bf.b1_firstx)
			bf.intersect_idx++;
		return (wall_front(r, r->bunches[bunch1].first_idx, bf.intersect_idx));
	}
	else
	{
		bf.intersect_idx = r->bunches[bunch1].first_idx;
		while (r->pvwalls[bf.intersect_idx].col1 < bf.b2_firstx)
			bf.intersect_idx++;
		return (wall_front(r, bf.intersect_idx, r->bunches[bunch2].first_idx));
	}
}
