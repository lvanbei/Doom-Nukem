/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:40 by hde-moff          #+#    #+#             */
/*   Updated: 2019/11/25 15:52:05 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

double			dist2(double x0, double y0, double x1, double y1)
{
	double		a;
	double		b;

	a = (x0 - x1);
	b = (y0 - y1);
	a *= a;
	b *= b;
	return (a + b);
}

static double	dist2_wallsq(double p_x, double p_y,
const t_v2f *w, const t_v2f *v)
{
	double		l2;
	double		t;
	t_v2f		tmp;

	l2 = dist2(v->x, v->y, w->x, w->y);
	if (l2 == 0.0)
		return (dist2(p_x, p_y, v->x, v->y));
	t = ((p_x - v->x) * (w->x - v->x) + (p_y - v->y) * (w->y - v->y)) / l2;
	t = fmax(0, fmin(1, t));
	tmp = (t_v2f) {v->x + (t * (w->x - v->x)), v->y + (t * (w->y - v->y)) };
	return (dist2(p_x, p_y, tmp.x, tmp.y));
}

double			w2p_dist(const t_wall *w1, const t_wall *w2, double p_x,
double p_y)
{
	t_v2f		w;
	t_v2f		v;

	w = (t_v2f) {w1->x, w1->y};
	v = (t_v2f) {w2->x, w2->y};
	return (sqrt(dist2_wallsq(p_x, p_y, &w, &v)));
}
