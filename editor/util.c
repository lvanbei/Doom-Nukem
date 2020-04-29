/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int		wall_intersects2(t_ed *ed, t_wall_inter *wi)
{
	wi->w2 = (t_line2f) {ed->walls[wi->i].x, ed->walls[wi->i].y,
		ed->walls[ed->walls[wi->i].next_wall].x,
		ed->walls[ed->walls[wi->i].next_wall].y};
	wi->min_0 = fmin(wi->w.x0, wi->w.x1);
	wi->max_0 = fmax(wi->w.x0, wi->w.x1);
	wi->min_1 = fmin(wi->w2.x0, wi->w2.x1);
	wi->max_1 = fmax(wi->w2.x0, wi->w2.x1);
	if (wi->min_1 > wi->max_0 || wi->max_1 < wi->min_0)
		return (0);
	wi->min_0 = fmin(wi->w.y0, wi->w.y1);
	wi->max_0 = fmax(wi->w.y0, wi->w.y1);
	wi->min_1 = fmin(wi->w2.y0, wi->w2.y1);
	wi->max_1 = fmax(wi->w2.y0, wi->w2.y1);
	if (wi->min_1 > wi->max_0 || wi->max_1 < wi->min_0)
		return (0);
	if ((wi->w.x0 == wi->w2.x0 && wi->w.y0 == wi->w2.y0)
			|| (wi->w.x0 == wi->w2.x1 && wi->w.y0 == wi->w2.y1)
			|| (wi->w.x1 == wi->w2.x0 && wi->w.y1 == wi->w2.y0)
			|| (wi->w.x1 == wi->w2.x1 && wi->w.y1 == wi->w2.y1))
		return (0);
	return (1);
}

int				wall_intersects(t_ed *ed, int wall_id, int num_walls)
{
	t_wall_inter	wi;

	wi.w = (t_line2f) {ed->walls[wall_id].x, ed->walls[wall_id].y,
		ed->walls[ed->walls[wall_id].next_wall].x,
		ed->walls[ed->walls[wall_id].next_wall].y};
	wi.i = -1;
	while (++wi.i < num_walls)
	{
		if (wi.i == wall_id)
			continue ;
		if (!wall_intersects2(ed, &wi))
			continue ;
		if (line_intersection(wi.w, wi.w2, NULL, NULL))
			return (1);
	}
	return (0);
}

int				inside_sector(t_ed *ed, double x, double y, int num_sector)
{
	int			hits;
	int			i;
	t_line2f	l;

	hits = 0;
	i = ed->sectors[num_sector].start_wall - 1;
	while (++i < ed->sectors[num_sector].start_wall +
			ed->sectors[num_sector].num_walls)
	{
		l = (t_line2f) {ed->walls[i].x, ed->walls[i].y,
			ed->walls[ed->walls[i].next_wall].x,
			ed->walls[ed->walls[i].next_wall].y};
		if ((x == l.x0 && y == l.y0) || (x == l.x1 && y == l.y1))
			return (-1);
		if ((l.y0 > y) != (l.y1 > y) && (x < (l.x1 - l.x0) * (y - l.y0) /
					(l.y1 - l.y0) + l.x0))
			hits = !hits;
	}
	return (hits);
}

int				get_parent_sector(t_ed *ed, double x, double y)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < ed->num_sectors)
	{
		ret = inside_sector(ed, x, y, i);
		if (ret > 0)
			return (i);
		else if (ret == -1)
			return (-2);
	}
	return (-1);
}
