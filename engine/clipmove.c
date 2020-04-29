/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipmove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:40 by hde-moff          #+#    #+#             */
/*   Updated: 2019/11/25 15:52:05 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void				clipmove_init_func(t_thing *thing, t_v3f *vec,
		t_clipmove_struct *cm, int flags)
{
	cm->ret = 1;
	cm->radius = sqrtf((vec->x * vec->x) + (vec->y * vec->y)) + WALLDIST;
	cm->x = thing->x;
	cm->y = thing->y;
	cm->z = thing->z;
	cm->goalx = cm->x + vec->x;
	cm->goaly = cm->y + vec->y;
	cm->center_x = (cm->goalx + cm->x) / 2;
	cm->center_y = (cm->goaly + cm->y) / 2;
	cm->cb.xmin = cm->center_x - cm->radius;
	cm->cb.xmax = cm->center_x + cm->radius;
	cm->cb.ymin = cm->center_y - cm->radius;
	cm->cb.ymax = cm->center_y + cm->radius;
	cm->cb.xv = vec->x;
	cm->cb.yv = vec->y;
	cm->cb.zv = vec->z;
	cm->flags = flags;
}

static inline void	clipmove_project(t_clipmove_struct *cm, double vecz)
{
	cm->tmp_x = cm->goalx;
	cm->tmp_y = cm->goaly;
	cm->ret = -2;
	cm->hit = raytrace(cm);
	if (cm->hit >= 0)
	{
		if (cm->cl.line_thing_id[cm->hit] != -1)
			cm->ret = cm->cl.line_thing_id[cm->hit];
		else
			cm->ret = -1;
	}
	cm->x = cm->tmp_x;
	cm->y = cm->tmp_y;
	cm->z += vecz;
}

static inline void	cm_one_liner(t_clipmove_struct *cm)
{
	cm->tmp_x = cm->goalx;
	cm->tmp_y = cm->goaly;
}

static inline int	clipslide_player(t_clipmove_struct *cm, t_v3f vec)
{
	cm_one_liner(cm);
	if ((cm->hitwall = raytrace(cm)) >= 0)
	{
		cm->wx = cm->cl.lines[cm->hitwall].x1 - cm->cl.lines[cm->hitwall].x0;
		cm->wy = cm->cl.lines[cm->hitwall].y1 - cm->cl.lines[cm->hitwall].y0;
		cm->l2 = (cm->wx * cm->wx) + (cm->wy * cm->wy);
		cm->l1 = (cm->goalx - cm->tmp_x) * cm->wx + (cm->goaly - cm->tmp_y)
			* cm->wy;
		cm->l3 = cm->l1 / cm->l2;
		cm->goalx = (cm->wx * cm->l3) + cm->tmp_x;
		cm->goaly = (cm->wy * cm->l3) + cm->tmp_y;
		cm->i2 = (cm->wx * vec.x) + (cm->wy * vec.y);
		cm->i = cm->cnt - 1;
		while (cm->i >= 0)
		{
			cm->j = cm->hitwalls[cm->i];
			cm->i3 = ((cm->cl.lines[cm->j].x1 - cm->cl.lines[cm->j].x0) * vec.x)
				+ ((cm->cl.lines[cm->j].y1 - cm->cl.lines[cm->j].y0) * vec.y);
			if ((cm->i2 ^ cm->i3) < 0)
				return (2);
			cm->i--;
		}
		cm->hitwalls[cm->cnt] = cm->hitwall;
	}
	return (1);
}

int					clipmove(t_engine *eng, t_thing *thing, t_v3f vec,
		int flags)
{
	t_clipmove_struct cm;

	if (vec.x == 0 && vec.y == 0)
		return (0);
	clipmove_init_func(thing, &vec, &cm, flags);
	fill_cliplines(eng, thing, thing->sector, &cm);
	if (flags & CLIPMOVE_F_PROJ)
		clipmove_project(&cm, vec.z);
	else
	{
		cm.hitwall = 0;
		cm.cnt = 0;
		while (cm.hitwall >= 0 && cm.cnt < MAX_CLIPSLIDES)
		{
			if (clipslide_player(&cm, vec) == 2)
				return (clipmove_end_func(eng, thing, &cm));
			cm.cnt++;
			cm.x = cm.tmp_x;
			cm.y = cm.tmp_y;
		}
	}
	return (clipmove_end_func(eng, thing, &cm));
}
