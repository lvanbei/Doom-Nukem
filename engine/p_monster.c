/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_monster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline int		wall_out_of_bounds(const t_line2f *w, t_box b)
{
	if (w->x0 < b.xmin && w->x1 < b.xmin)
		return (1);
	if (w->x0 > b.xmax && w->x1 > b.xmax)
		return (1);
	if (w->y0 < b.ymin && w->y1 < b.ymin)
		return (1);
	if (w->y0 > b.ymax && w->y1 > b.ymax)
		return (1);
	return (0);
}

static inline void		create_box(t_engine *eng, t_see_player *sp)
{
	if (sp->monster.x < eng->player.x)
	{
		sp->b.xmin = sp->monster.x;
		sp->b.xmax = eng->player.x;
	}
	else
	{
		sp->b.xmin = eng->player.x;
		sp->b.xmax = sp->monster.x;
	}
	if (sp->monster.y < eng->player.y)
	{
		sp->b.ymin = sp->monster.y;
		sp->b.ymax = eng->player.y;
	}
	else
	{
		sp->b.ymin = eng->player.y;
		sp->b.ymax = sp->monster.y;
	}
}

static int				monster_can_see_player(t_engine *eng, int thing_id)
{
	t_see_player	sp;

	sp.monster = eng->things[thing_id];
	create_box(eng, &sp);
	sp.i = 0;
	while (sp.i < eng->num_walls)
	{
		sp.w = (t_line2f) {eng->walls[sp.i].x, eng->walls[sp.i].y,
			eng->walls[eng->walls[sp.i].next_wall].x,
			eng->walls[eng->walls[sp.i].next_wall].y};
		if ((eng->walls[sp.i].next_sector != -1 &&
				(eng->walls[sp.i].flags & WALL_FLAG_OPEN)) ||
				wall_out_of_bounds(&sp.w, sp.b))
		{
			sp.i++;
			continue ;
		}
		if (get_line_intersection((t_line2f) {sp.w.x0,
					sp.w.y0, sp.w.x1, sp.w.y1},
					(t_line2f) {eng->player.x, eng->player.y,
					sp.monster.x, sp.monster.y}, &sp.p.x, &sp.p.y))
			return (0);
		sp.i++;
	}
	return (1);
}

static inline void		move_monster(t_m_monster *m)
{
	m->xv = m->eng->player.x - m->monster->x;
	m->yv = m->eng->player.y - m->monster->y;
	m->xv /= m->len;
	m->yv /= m->len;
	m->xv *= MONSTER_METERS_PER_SECOND * m->f_delta;
	m->yv *= MONSTER_METERS_PER_SECOND * m->f_delta;
	m->monster->z = m->monster->z + (m->monster->zv * m->f_delta * 5);
	m->monster->zv = m->monster->zv + (-2 * m->f_delta * 5);
	if (m->monster->z + PLAYER_CEILING_CLIP >
			m->eng->sectors[m->monster->sector].ceiling_height)
		m->monster->z = m->eng->sectors[m->monster->sector].ceiling_height -
			PLAYER_CEILING_CLIP;
	if (m->monster->z < m->eng->sectors[m->monster->sector].floor_height +
			m->eng->thing_height[m->monster->type])
	{
		m->monster->z = m->eng->sectors[m->monster->sector].floor_height +
			m->eng->thing_height[m->monster->type];
		m->monster->zv = 0.0f;
	}
	clipmove(m->eng, m->monster, (t_v3f) {m->xv, m->yv, 0.0f}, 0);
	pushmove(m->eng, m->monster, m->monster->sector);
}

void					update_monster(t_engine *eng, int thing_id,
		double f_delta)
{
	t_m_monster m;

	m.eng = eng;
	m.thing_id = thing_id;
	m.f_delta = f_delta;
	m.monster = &eng->things[thing_id];
	m.len = line_len(eng->player.x, eng->player.y, m.monster->x, m.monster->y);
	if (m.len < MONSTER_SPOT_RADIUS && m.len > MONSTER_DAMAGE_RADIUS &&
			monster_can_see_player(eng, thing_id))
		move_monster(&m);
}
