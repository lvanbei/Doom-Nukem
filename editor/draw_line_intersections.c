/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_intersections.                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static inline double	get_x_intersect(double x, t_line2f l)
{
	double m;

	if (l.x0 == l.x1)
		return (x);
	m = (l.y1 - l.y0) / (l.x1 - l.x0);
	return ((m * x) - (m * l.x0) + l.y0);
}

static inline double	get_y_intersect(double y, t_line2f l)
{
	double	m;

	if (l.y0 == l.y1)
		return (y);
	m = (l.y1 - l.y0) / (l.x1 - l.x0);
	return (((y - l.y0) / m) + l.x0);
}

static inline void		intersections2(t_line2f *l, t_box b)
{
	if (l->y0 < b.ymin)
	{
		l->x0 = get_y_intersect(b.ymin, *l);
		l->y0 = b.ymin;
	}
	else if (l->y1 < b.ymin)
	{
		l->x1 = get_y_intersect(b.ymin, *l);
		l->y1 = b.ymin;
	}
	if (l->y0 >= b.ymax)
	{
		l->x0 = get_y_intersect(b.ymax, *l);
		l->y0 = b.ymax;
	}
	else if (l->y1 >= b.ymax)
	{
		l->x1 = get_y_intersect(b.ymax, *l);
		l->y1 = b.ymax;
	}
}

void					intersections(t_line2f *l, t_box b)
{
	if (l->x0 < b.xmin)
	{
		l->y0 = get_x_intersect(b.xmin, *l);
		l->x0 = b.xmin;
	}
	else if (l->x1 < b.xmin)
	{
		l->y1 = get_x_intersect(b.xmin, *l);
		l->x1 = b.xmin;
	}
	if (l->x0 >= b.xmax)
	{
		l->y0 = get_x_intersect(b.xmax, *l);
		l->x0 = b.xmax;
	}
	else if (l->x1 >= b.xmax)
	{
		l->y1 = get_x_intersect(b.xmax, *l);
		l->x1 = b.xmax;
	}
	intersections2(l, b);
}
