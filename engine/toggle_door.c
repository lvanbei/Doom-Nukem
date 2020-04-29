/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int				get_co_wall(t_engine *eng, int idx_w)
{
	t_line2f	l;
	int			i;
	int			j;

	l = (t_line2f) {eng->walls[idx_w].x, eng->walls[idx_w].y,
		eng->walls[eng->walls[idx_w].next_wall].x,
		eng->walls[eng->walls[idx_w].next_wall].y};
	i = -1;
	while (++i < eng->num_walls)
	{
		if (eng->walls[i].x == l.x0 && eng->walls[i].y == l.y0 && i != idx_w)
		{
			if (eng->walls[eng->walls[i].next_wall].x == l.x1
					&& eng->walls[eng->walls[i].next_wall].y == l.y1)
				return (i);
			j = -1;
			while (++j < eng->num_walls)
			{
				if (eng->walls[j].next_wall == i
						&& eng->walls[j].x == l.x1 && eng->walls[j].y == l.y1)
					return (j);
			}
		}
	}
	return (-1);
}

static inline int		get_nearest_wall(t_engine *eng)
{
	t_gnw	g;

	g.hit = -1;
	g.dist = 1.0f;
	g.p_x = eng->player.x;
	g.p_y = eng->player.y;
	g.i = -1;
	while (++g.i < eng->num_walls)
	{
		g.w1 = &eng->walls[g.i];
		g.w2 = &eng->walls[g.w1->next_wall];
		g.tmp = w2p_dist(g.w1, g.w2, g.p_x, g.p_y);
		if (g.tmp < g.dist)
		{
			g.dist = g.tmp;
			g.hit = g.i;
		}
	}
	return (g.hit);
}

static inline void		init_open_walls2(t_engine *eng, t_iow i)
{
	i.sect1 = get_sector(eng, i.nearest);
	i.sect2 = get_sector(eng, i.match);
	eng->door_bounds[0] = fmax(eng->sectors[i.sect1].floor_height,
			eng->sectors[i.sect2].floor_height);
	eng->door_bounds[1] = fmin(eng->sectors[i.sect1].ceiling_height,
			eng->sectors[i.sect2].ceiling_height);
	if (eng->walls[i.nearest].door_height == eng->door_bounds[0])
		eng->door_state = DS_OPENING;
	else if (eng->walls[i.nearest].door_height == eng->door_bounds[1])
		eng->door_state = DS_CLOSING;
	else
		abort_error(eng, "door (%d) height (%f) in between (%f, %f)\n",
				i.nearest, eng->walls[i.nearest].door_height
				, eng->door_bounds[0], eng->door_bounds[1]);
	eng->doors_opening[0] = i.nearest;
	eng->doors_opening[1] = i.match;
	Mix_PlayChannel(-1, eng->p_i.ui_sound[UI_SOUND_BUTTON], 0);
	Mix_PlayChannel(-1, eng->p_i.ui_sound[UI_SOUND_DOORMOVE], 0);
}

void					init_open_walls(t_engine *eng)
{
	t_iow	i;

	if (eng->doors_opening[0] != -1)
		return ;
	i.nearest = get_nearest_wall(eng);
	if (i.nearest == -1)
		return ;
	i.match = get_co_wall(eng, i.nearest);
	if (i.match == -1)
		return ;
	if (eng->walls[i.nearest].next_sector == -1
			|| eng->walls[i.match].next_sector == -1)
		return ;
	if (eng->walls[i.nearest].m_texture == -1
			|| eng->walls[i.match].m_texture == -1)
		return ;
	if (eng->walls[i.nearest].door_height != eng->walls[i.match].door_height)
		abort_error(eng,
				"door Height different on door sides (%d: %F, %d: %F)\n",
				i.nearest, eng->walls[i.nearest].door_height, i.match,
				eng->walls[i.match].door_height);
	init_open_walls2(eng, i);
}
