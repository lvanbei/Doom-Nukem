/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:02:04 by hde-moff          #+#    #+#             */
/*   Updated: 2019/10/21 12:48:27 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	inside_sector(t_engine *eng, double x, double y, int num_sector)
{
	t_line2f	l;
	int			hits;
	int			i;

	if (num_sector < 0 || num_sector >= eng->num_sectors)
		return (0);
	hits = 0;
	i = eng->sectors[num_sector].start_wall - 1;
	while (++i < eng->sectors[num_sector].start_wall +
			eng->sectors[num_sector].num_walls)
	{
		l.y0 = ((double)eng->walls[i].y);
		l.y1 = ((double)eng->walls[eng->walls[i].next_wall].y);
		l.x0 = ((double)eng->walls[i].x);
		l.x1 = ((double)eng->walls[eng->walls[i].next_wall].x);
		if ((l.y0 > y) != (l.y1 > y) && (x < (l.x1 - l.x0) * (y - l.y0)
					/ (l.y1 - l.y0) + l.x0))
			hits = !hits;
	}
	return (hits);
}

int	update_thing_sector(t_engine *eng, t_thing *thing, double x, double y)
{
	int i;

	i = -1;
	if (thing->sector >= 0 && thing->sector < eng->num_sectors)
	{
		if (inside_sector(eng, x, y, thing->sector))
			return (thing->sector);
		i = eng->sectors[thing->sector].start_wall;
		while (++i < eng->sectors[thing->sector].start_wall +
				eng->sectors[thing->sector].num_walls)
		{
			if (eng->walls[i].next_sector != -1)
			{
				if (inside_sector(eng, x, y, eng->walls[i].next_sector))
					return (eng->walls[i].next_sector);
			}
		}
	}
	i = -1;
	while (++i < eng->num_sectors)
	{
		if (inside_sector(eng, x, y, i))
			return (i);
	}
	return (-1);
}
