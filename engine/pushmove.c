/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushmove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:40 by hde-moff          #+#    #+#             */
/*   Updated: 2019/11/25 15:52:05 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline int	wd_p_exits_box(t_line2f l, double *px, double *py)
{
	if (get_line_intersection((t_line2f) {l.x0, l.y0, l.x1, l.y1},
				(t_line2f) {WD, WD, WD, -WD}, px, py)
			|| get_line_intersection((t_line2f) {l.x0, l.y0, l.x1, l.y1},
				(t_line2f) {-WD, WD, WD, WD}, px, py)
			|| get_line_intersection((t_line2f) {l.x0, l.y0, l.x1, l.y1},
				(t_line2f) {-WD, WD, -WD, -WD}, px, py)
			|| get_line_intersection((t_line2f) {l.x0, l.y0, l.x1, l.y1},
				(t_line2f) {-WD, -WD, WD, -WD}, px, py))
		return (1);
	return (0);
}

static int			p_in_walldist(t_engine *eng, double x, double y,
		int wallnum)
{
	t_walldist wd;

	wd.x0 = eng->walls[wallnum].x - x;
	wd.y0 = eng->walls[wallnum].y - y;
	wd.x1 = eng->walls[eng->walls[wallnum].next_wall].x - x;
	wd.y1 = eng->walls[eng->walls[wallnum].next_wall].y - y;
	if (wd.x0 < -WALLDIST && wd.x1 < -WALLDIST)
		return (0);
	if (wd.x0 > WALLDIST && wd.x1 > WALLDIST)
		return (0);
	if (wd.y0 < -WALLDIST && wd.y1 < -WALLDIST)
		return (0);
	if (wd.y0 > WALLDIST && wd.y1 > WALLDIST)
		return (0);
	if (wd.x0 < WALLDIST && wd.x0 > -WALLDIST
			&& wd.y0 < WALLDIST && wd.y0 > -WALLDIST
			&& wd.x1 < WALLDIST && wd.x1 > -WALLDIST
			&& wd.y1 < WALLDIST && wd.y1 > -WALLDIST)
		return (1);
	return (wd_p_exits_box((t_line2f){wd.x0, wd.y0, wd.x1, wd.y1},
				&wd.px, &wd.py));
}

static inline int	pushmove2(t_engine *eng, t_thing *thing,
		t_pushmove *pm)
{
	pm->w = (t_line2f) {eng->walls[pm->i].x, eng->walls[pm->i].y,
		eng->walls[eng->walls[pm->i].next_wall].x,
		eng->walls[eng->walls[pm->i].next_wall].y};
	pm->nx = pm->w.y1 - pm->w.y0;
	pm->ny = -(pm->w.x1 - pm->w.x0);
	pm->wall_len = l_line_len(&pm->w);
	pm->nx /= (pm->wall_len * 27);
	pm->ny /= (pm->wall_len * 27);
	pm->tries = 0;
	while (p_in_walldist(eng, thing->x, thing->y, pm->i))
	{
		if (pm->tries == 10)
		{
			ft_printf("overflowed pushmove tries\n");
			return (-1);
		}
		thing->x += pm->nx;
		thing->y += pm->ny;
		pm->tries++;
	}
	return (1);
}

static inline int	pm_height_no_conflict(t_engine *eng, t_thing *thing,
		int sectnum, t_pushmove *pm)
{
	if (eng->walls[pm->i].next_sector != -1)
	{
		if (eng->sectors[eng->walls[pm->i].next_sector].floor_height <=
				pm->base_height)
		{
			if (thing->z <
					fmin(
						eng->sectors[sectnum].ceiling_height,
						eng->sectors[eng->walls[pm->i].next_sector].CH))
			{
				pm->i++;
				return (1);
			}
		}
	}
	return (0);
}

int					pushmove(t_engine *eng, t_thing *thing, int sectnum)
{
	t_pushmove pm;

	pm.last_wall = eng->sectors[sectnum].start_wall
		+ eng->sectors[sectnum].num_walls;
	pm.base_height = (thing->z - eng->thing_height[thing->type]) + STEP_HEIGHT;
	if (thing == &eng->player && (eng->player_flags & PF_CROUCH))
		pm.base_height += 0.25f;
	pm.i = eng->sectors[sectnum].start_wall;
	while (pm.i < pm.last_wall)
	{
		if (p_in_walldist(eng, thing->x, thing->y, pm.i))
		{
			if (pm_height_no_conflict(eng, thing, sectnum, &pm))
				continue ;
			if (pushmove2(eng, thing, &pm) == -1)
				return (-1);
			thing->sector = update_thing_sector(eng, thing, thing->x, thing->y);
			pm.i = eng->sectors[sectnum].start_wall;
		}
		pm.i++;
	}
	return (1);
}
