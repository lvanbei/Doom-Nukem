/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_wall2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int				tl_wall2(t_ed *ed, t_tl_wallf *tw)
{
	tw->last_wall_idx = ed->num_walls + ed->tl_w.num_walls - 1;
	ed->walls[tw->last_wall_idx].next_wall = ed->num_walls;
	if (wall_intersects(ed, tw->last_wall_idx, tw->last_wall_idx)
			|| tw->parent_sector == -2)
	{
		ed->walls[tw->last_wall_idx].next_wall = tw->last_wall_idx + 1;
		return (0);
	}
	if (ed->num_sectors >= MAX_SECTORS)
		abort_error(ed, "overflowed sectors\n");
	ed->sectors[ed->num_sectors].start_wall = ed->num_walls;
	ed->sectors[ed->num_sectors].num_walls = ed->tl_w.num_walls;
	ed->sectors[ed->num_sectors].floor_height = ed->tl_w.default_floor_height;
	ed->sectors[ed->num_sectors].ceiling_height =
		ed->tl_w.default_ceiling_height;
	ed->sectors[ed->num_sectors].floor_texture =
		ed->tl_w.default_floor_texture;
	ed->sectors[ed->num_sectors].ceiling_texture =
		ed->tl_w.default_ceiling_texture;
	tw->stored_clockwise = sector_is_clockwise(ed, ed->num_sectors);
	if (!tw->stored_clockwise)
		set_link_prev(ed, ed->sectors[ed->num_sectors].start_wall,
				(ed->sectors[ed->num_sectors].start_wall +
				ed->sectors[ed->num_sectors].num_walls) - 1);
	return (1);
}

void					tl_wall3(t_ed *ed, t_tl_wallf *tw)
{
	tw->end_wall = ed->num_walls + ed->tl_w.num_walls;
	tw->i = ed->num_walls - 1;
	while (++tw->i < tw->end_wall)
	{
		tw->match = get_co_wall(ed, tw->i);
		if (tw->match != -1)
		{
			tw->w2_sect = get_sector(ed, tw->match);
			ed->walls[tw->match].m_texture = -1;
			ed->walls[tw->match].flags = WALL_FLAG_OPEN;
			ed->walls[tw->match].next_sector = ed->num_sectors;
			ed->walls[tw->i].m_texture = -1;
			ed->walls[tw->i].flags = WALL_FLAG_OPEN;
			ed->walls[tw->i].next_sector = tw->w2_sect;
		}
	}
	ed->num_walls += ed->tl_w.num_walls;
}

void					tl_wall4(t_ed *ed, t_tl_wallf *tw)
{
	ed->num_walls += ed->tl_w.num_walls;
	tw->o_end_of_parent_sect = ed->sectors[tw->parent_sector].start_wall
		+ ed->sectors[tw->parent_sector].num_walls;
	tw->parent_sect_end = &ed->walls[tw->o_end_of_parent_sect];
	slow_memmove(tw->parent_sect_end + ed->tl_w.num_walls, tw->parent_sect_end,
			sizeof(t_wall) * (&ed->walls[tw->last_wall_idx] -
				tw->parent_sect_end + 1));
	tw->i = tw->o_end_of_parent_sect + ed->tl_w.num_walls - 1;
	while (++tw->i < ed->num_walls)
		if (ed->walls[tw->i].next_wall != -1)
			ed->walls[tw->i].next_wall += ed->tl_w.num_walls;
	ed->sectors[tw->parent_sector].num_walls += ed->tl_w.num_walls;
	tw->i = tw->parent_sector;
	while (++tw->i < ed->num_sectors + 1)
		ed->sectors[tw->i].start_wall += ed->tl_w.num_walls;
	tw->new_sect = &ed->walls[ed->sectors[ed->num_sectors].start_wall];
	slow_memcpy(tw->parent_sect_end, tw->new_sect,
			(sizeof(t_wall) * ed->tl_w.num_walls));
	if (tw->stored_clockwise)
		set_link_prev(ed, tw->o_end_of_parent_sect,
				(tw->o_end_of_parent_sect + ed->tl_w.num_walls) - 1);
	else
		set_link_next(ed, tw->o_end_of_parent_sect,
				(tw->o_end_of_parent_sect + ed->tl_w.num_walls) - 1);
}

void					tl_wall(t_ed *ed, int screen_x, int screen_y)
{
	static t_tl_wallf tw = {.parent_sector = -2};

	screen_to_map_round(&ed->view, (t_v2) {screen_x, screen_y},
			&tw.p_x, &tw.p_y);
	if (ed->tl_w.num_walls > 0)
	{
		if (ed->tl_w.num_walls > 2 &&
				ed->walls[ed->num_walls].x == tw.p_x
				&& ed->walls[ed->num_walls].y == tw.p_y)
		{
			if (!tl_wall2(ed, &tw))
				return ;
			tl_wall3(ed, &tw);
			if (tw.parent_sector >= 0)
				tl_wall4(ed, &tw);
			ed->num_sectors++;
			ed->tl_w.num_walls = 0;
			tw.parent_sector = -2;
			return ;
		}
		if (!tl_wall5(ed, &tw))
			return ;
	}
	append_wall(ed, tw.p_x, tw.p_y, ed->num_walls + ed->tl_w.num_walls + 1);
}
