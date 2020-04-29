/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line,c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static inline int		is_out_of_box(t_line2f l, t_box b)
{
	if ((l.x0 < b.xmin && l.x1 < b.xmin)
			|| (l.x0 > b.xmax && l.x1 > b.xmax)
			|| (l.y0 < b.ymin && l.y1 < b.ymin)
			|| (l.y0 > b.ymax && l.y1 > b.ymax))
		return (1);
	return (0);
}

static inline int		is_out_of_box2(t_line2f l, t_box b)
{
	if ((l.x0 < b.xmin || l.x1 < b.xmin)
			|| (l.x0 > b.xmax || l.x1 > b.xmax)
			|| (l.y0 < b.ymin || l.y1 < b.ymin)
			|| (l.y0 > b.ymax || l.y1 > b.ymax))
		return (1);
	return (0);
}

void					draw_line2_clipped(t_ed *ed, t_line2f l, int color)
{
	t_box		b;
	t_line2f	dest;
	t_line2		d;

	b = (t_box) {ed->view.xmin, ed->view.ymin, ed->view.xmin + ed->view.w,
		ed->view.ymin + ed->view.w};
	if (is_out_of_box(l, b))
		return ;
	intersections(&l, b);
	if (is_out_of_box2(l, b))
		return ;
	map_to_screen(&ed->view, (t_v2f) {l.x0, l.y0}, &dest.x0, &dest.y0);
	map_to_screen(&ed->view, (t_v2f) {l.x1, l.y1}, &dest.x1, &dest.y1);
	d = (t_line2) {dest.x0, dest.y0, dest.x1, dest.y1};
	if (d.x0 == GRID_WIDTH)
		d.x0 = GRID_WIDTH - 1;
	if (d.x1 == GRID_WIDTH)
		d.x1 = GRID_WIDTH - 1;
	if (d.y0 == -1)
		d.y0 = 0;
	if (d.y1 == -1)
		d.y1 = 0;
	draw_line(ed->surface, d, color);
}
