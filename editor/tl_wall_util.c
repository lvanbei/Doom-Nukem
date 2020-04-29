/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_wall_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int				point_match(t_ed *ed, int i, t_line2f l)
{
	if (ed->walls[ed->walls[i].next_wall].x == l.x1
			&& ed->walls[ed->walls[i].next_wall].y == l.y1)
		return (1);
	return (0);
}

int				get_co_wall(t_ed *ed, int idx_w)
{
	t_line2f	l;
	int			i[2];

	l = (t_line2f) { ed->walls[idx_w].x, ed->walls[idx_w].y,
	ed->walls[ed->walls[idx_w].next_wall].x,
	ed->walls[ed->walls[idx_w].next_wall].y};
	i[0] = -1;
	while (++i[0] < ed->num_walls)
	{
		if (ed->walls[i[0]].x == l.x0 && ed->walls[i[0]].y == l.y0 &&
				i[0] != idx_w)
		{
			if (point_match(ed, i[0], l))
				return (i[0]);
			i[1] = -1;
			while (++i[1] < ed->num_walls)
			{
				if (ed->walls[i[1]].next_wall == i[0]
						&& ed->walls[i[1]].x == l.x1 && ed->walls[i[1]].y
						== l.y1)
					return (i[1]);
			}
		}
	}
	return (-1);
}

void			screen_to_map_round(t_view *view, t_v2 p,
		double *dest_x, double *dest_y)
{
	*dest_x = view->xmin + (p.x * view->dx_1);
	*dest_y = (-(p.y - (GRID_HEIGHT + 1)) * view->dx_1) + view->ymin;
	*dest_x = round(*dest_x);
	*dest_y = round(*dest_y);
}

int				tl_wall5(t_ed *ed, t_tl_wallf *tw)
{
	tw->i = ed->num_walls;
	while (++tw->i < ed->num_walls + ed->tl_w.num_walls)
		if (ed->walls[tw->i].x == tw->p_x && ed->walls[tw->i].y == tw->p_y)
			return (0);
	if (tw->parent_sector == -2)
		tw->parent_sector = get_parent_sector(ed, tw->p_x, tw->p_y);
	return (1);
}
