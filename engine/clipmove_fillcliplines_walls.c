/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipmove_fillcliplines_walls.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:40 by hde-moff          #+#    #+#             */
/*   Updated: 2019/11/25 15:52:05 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline void	handle_portal2(t_engine *eng, t_thing *thing,
		t_clipmove_struct *cm, t_fillcliplines *fc)
{
	if (fc->w.m_texture != -1)
	{
		if (fc->w.door_height > fc->curr_sect_floor && fc->w.door_height >
				fc->new_sect_floor)
			fc->new_sect_ceil = fc->w.door_height;
		else
			fc->clip = 1;
	}
	if ((fc->nx * cm->cb.xv) + (fc->ny * cm->cb.yv) >= 0)
		fc->clip = 0;
	else
	{
		if (fc->curr_sect_floor < fc->new_sect_floor)
		{
			if ((thing->z - eng->thing_height[thing->type]) + STEP_HEIGHT <=
					fc->new_sect_floor)
				fc->clip = 1;
		}
		if (fc->curr_sect_ceil > fc->new_sect_ceil)
		{
			if (thing->z > fc->new_sect_ceil)
				fc->clip = 1;
		}
	}
}

static inline void	handle_portal(t_engine *eng, t_thing *thing,
		t_clipmove_struct *cm, t_fillcliplines *fc)
{
	fc->curr_sect_floor = eng->sectors[fc->sectnum].floor_height;
	fc->new_sect_floor = eng->sectors[fc->w.next_sector].floor_height;
	fc->curr_sect_ceil = eng->sectors[fc->sectnum].ceiling_height;
	fc->new_sect_ceil = eng->sectors[fc->w.next_sector].ceiling_height;
	handle_portal2(eng, thing, cm, fc);
	if (fc->clip == 0)
	{
		fc->j = cm->cl.num_clipsects - 1;
		while (fc->j >= 0)
		{
			if (fc->w.next_sector == cm->cl.clipsects[fc->j])
				break ;
			fc->j--;
		}
		if (fc->j < 0)
			cm->cl.clipsects[cm->cl.num_clipsects++] = fc->w.next_sector;
	}
}

static inline void	append_wall_cliplines(t_clipmove_struct *cm,
		t_fillcliplines *fc)
{
	fc->x_dist = (cm->cb.xv > 0) ? WALLDIST : -WALLDIST;
	cm->cl.lines[fc->clipline_idx++] =
		(t_line2f) {fc->w.x - fc->x_dist, fc->w.y - fc->x_dist,
			fc->w.x - fc->x_dist, fc->w.y + fc->x_dist};
	cm->cl.lines[fc->clipline_idx++] =
		(t_line2f) {fc->w2.x - fc->x_dist, fc->w2.y - fc->x_dist,
			fc->w2.x - fc->x_dist, fc->w2.y + fc->x_dist};
	fc->x_dist = (cm->cb.yv > 0) ? WALLDIST : -WALLDIST;
	cm->cl.lines[fc->clipline_idx++] =
		(t_line2f) {fc->w.x + fc->x_dist, fc->w.y - fc->x_dist,
			fc->w.x - fc->x_dist, fc->w.y - fc->x_dist};
	cm->cl.lines[fc->clipline_idx++] =
		(t_line2f) {fc->w2.x + fc->x_dist, fc->w2.y - fc->x_dist,
			fc->w2.x - fc->x_dist, fc->w2.y - fc->x_dist};
	fc->x_dist = (fc->dy > 0) ? WALLDIST : -WALLDIST;
	fc->y_dist = (fc->dx < 0) ? WALLDIST : -WALLDIST;
	cm->cl.lines[fc->clipline_idx++] =
		(t_line2f) {fc->w.x + fc->x_dist, fc->w.y + fc->y_dist,
			fc->w2.x + fc->x_dist, fc->w2.y + fc->y_dist};
	cm->cl.num_lines += 5;
}

void				fill_walls_sub(t_engine *eng, t_fillcliplines *fc,
		t_clipmove_struct *cm, t_thing *thing)
{
	fc->clip = 0;
	if (fc->w.next_sector == -1)
		fc->clip = 1;
	else
		handle_portal(eng, thing, cm, fc);
	if (fc->clip)
		append_wall_cliplines(cm, fc);
}

void				fill_walls(t_engine *eng, t_thing *thing,
		t_clipmove_struct *cm, t_fillcliplines *fc)
{
	int i;

	i = fc->start_wall;
	while (i < fc->end_wall)
	{
		fc->w = eng->walls[i];
		fc->w2 = eng->walls[fc->w.next_wall];
		if (line_is_out_of_cb(cm, (t_line2f) {fc->w.x, fc->w.y,
					fc->w2.x, fc->w2.y}))
		{
			i++;
			continue ;
		}
		fc->dx = fc->w2.x - fc->w.x;
		fc->dy = fc->w2.y - fc->w.y;
		fc->nx = fc->dy;
		fc->ny = -(fc->dx);
		fc->dotp = ((thing->x - fc->w.x) * fc->nx) +
			((thing->y - fc->w.y) * fc->ny);
		if (fc->dotp >= 0)
			fill_walls_sub(eng, fc, cm, thing);
		i++;
	}
}
