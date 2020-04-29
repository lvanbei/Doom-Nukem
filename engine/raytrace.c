/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:40 by hde-moff          #+#    #+#             */
/*   Updated: 2019/11/25 15:52:05 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline void		line_inter_init(t_line2f *l1, t_line2f *l2,
		t_line_inter *li)
{
	li->s1_x = l1->x1 - l1->x0;
	li->s1_y = l1->y1 - l1->y0;
	li->s2_x = l2->x1 - l2->x0;
	li->s2_y = l2->y1 - l2->y0;
	li->s = (-li->s1_y * (l1->x0 - l2->x0) + li->s1_x * (l1->y0 - l2->y0))
		/ (-li->s2_x * li->s1_y + li->s1_x * li->s2_y);
	li->t = (li->s2_x * (l1->y0 - l2->y0) - li->s2_y * (l1->x0 - l2->x0))
		/ (-li->s2_x * li->s1_y + li->s1_x * li->s2_y);
}

char					get_line_intersection(t_line2f l1, t_line2f l2,
		double *p_x, double *p_y)
{
	t_line_inter li;

	line_inter_init(&l1, &l2, &li);
	if (li.s >= 0 && li.s <= 1 && li.t >= 0 && li.t <= 1)
	{
		if (p_x != NULL)
			*p_x = l1.x0 + (li.t * li.s1_x);
		if (p_y != NULL)
			*p_y = l1.y0 + (li.t * li.s1_y);
		return (1);
	}
	return (0);
}

static inline int		find_hitwall(t_raytrace *rt)
{
	t_line2f	l;
	int			w;

	w = 0;
	while (w < rt->cl->num_lines)
	{
		l = rt->cl->lines[w];
		if (get_line_intersection((t_line2f) {rt->startx, rt->starty,
					*(rt->goalx), *(rt->goaly)}, l, &rt->newx, &rt->newy))
		{
			if ((fabs(rt->startx - rt->newx) +
						fabs(rt->starty - rt->newy)) <
					(fabs(rt->startx - *(rt->goalx))
					+ fabs(rt->starty - *(rt->goaly))))
			{
				*(rt->goalx) = rt->newx;
				*(rt->goaly) = rt->newy;
				rt->hitwall = w;
			}
		}
		w++;
	}
	return (rt->hitwall);
}

static inline void		rt_init(t_clipmove_struct *cm, t_raytrace *rt)
{
	rt->cl = &cm->cl;
	rt->startx = cm->x;
	rt->starty = cm->y;
	rt->goalx = &cm->tmp_x;
	rt->goaly = &cm->tmp_y;
	rt->hitwall = -1;
}

int						raytrace(t_clipmove_struct *cm)
{
	t_raytrace rt;

	rt_init(cm, &rt);
	if (find_hitwall(&rt) == -1)
		return (-1);
	rt.vx = *(rt.goalx) - rt.startx;
	rt.vy = *(rt.goaly) - rt.starty;
	rt.len = sqrtf((rt.vx * rt.vx) + (rt.vy * rt.vy));
	if (rt.len > 0.2f)
	{
		rt.vx /= rt.len;
		rt.vy /= rt.len;
		rt.vx *= -0.1f;
		rt.vy *= -0.1f;
		*(rt.goalx) += rt.vx;
		*(rt.goaly) += rt.vy;
	}
	else
	{
		*(rt.goalx) = rt.startx;
		*(rt.goaly) = rt.starty;
	}
	return (rt.hitwall);
}
