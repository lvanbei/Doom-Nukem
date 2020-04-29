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

int						get_sector(t_ed *ed, int wall_id)
{
	int	i;
	int	last_wall;

	i = -1;
	while (++i < ed->num_sectors)
	{
		last_wall = ed->sectors[i].start_wall + ed->sectors[i].num_walls;
		if (ed->sectors[i].start_wall <= wall_id && wall_id < last_wall)
			return (i);
	}
	abort_error(ed, "couldn't find sector for wall: %d\n", wall_id);
	return (-1);
}

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

char					line_intersection(t_line2f l1, t_line2f l2,
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
