/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int				append_wall(t_ed *ed, int x, int y, int next_wall)
{
	if (ed->num_walls + ed->tl_w.num_walls >= MAX_WALLS)
		abort_error(ed, "appending wall: (%d, %d); num_walls: %d,"
				"tl_w num_walls: %d overflow max: %d\n",
				x, y, ed->num_walls, ed->tl_w.num_walls, MAX_WALLS);
	ed->walls[ed->num_walls + ed->tl_w.num_walls].x = x;
	ed->walls[ed->num_walls + ed->tl_w.num_walls].y = y;
	ed->walls[ed->num_walls + ed->tl_w.num_walls].next_wall = next_wall;
	ed->walls[ed->num_walls + ed->tl_w.num_walls].next_sector = -1;
	ed->walls[ed->num_walls + ed->tl_w.num_walls].b_texture =
		ed->tl_w.default_b_texture;
	ed->walls[ed->num_walls + ed->tl_w.num_walls].m_texture =
		ed->tl_w.default_m_texture;
	ed->walls[ed->num_walls + ed->tl_w.num_walls].t_texture =
		ed->tl_w.default_t_texture;
	if (ed->tl_w.num_walls)
	{
		if (wall_intersects(ed, (ed->num_walls + ed->tl_w.num_walls) - 1,
					(ed->num_walls + ed->tl_w.num_walls) - 1))
			return (0);
	}
	ed->tl_w.num_walls++;
	return (1);
}

void			set_link_next(t_ed *ed, int start_wall, int end_wall)
{
	int	i;

	i = start_wall - 1;
	while (++i < end_wall)
		ed->walls[i].next_wall = i + 1;
	ed->walls[end_wall].next_wall = start_wall;
}

void			set_link_prev(t_ed *ed, int start_wall, int end_wall)
{
	int	i;

	i = end_wall + 1;
	while (--i > start_wall)
		ed->walls[i].next_wall = i - 1;
	ed->walls[start_wall].next_wall = end_wall;
}

void			sector_is_clockwise2(t_ed *ed, int num_sector,
		t_sect_clock *sc)
{
	sc->next_wall_idx = ed->walls[sc->p_idx].next_wall;
	sc->prev_wall_idx = ed->sectors[num_sector].start_wall;
	sc->i = ed->sectors[num_sector].start_wall - 1;
	while (++sc->i < sc->end_wall)
	{
		if (ed->walls[sc->i].next_wall == sc->p_idx)
		{
			sc->prev_wall_idx = sc->i;
			break ;
		}
	}
	if (ed->walls[sc->prev_wall_idx].next_wall != sc->p_idx)
		abort_error(ed, "is_clockwise() couldn't find previous wall for sect:"
				"%d wall: %d\n", num_sector, sc->p_idx);
}

int				sector_is_clockwise(t_ed *ed, int num_sector)
{
	t_sect_clock	sc;

	sc.p_idx = ed->sectors[num_sector].start_wall;
	sc.end_wall = sc.p_idx + ed->sectors[num_sector].num_walls;
	sc.curr_x = ed->walls[sc.p_idx].x;
	sc.curr_y = ed->walls[sc.p_idx].y;
	sc.i = ed->sectors[num_sector].start_wall - 1;
	while (++sc.i < sc.end_wall)
	{
		if (ed->walls[sc.i].y < sc.curr_y)
		{
			sc.curr_y = ed->walls[sc.i].y;
			sc.curr_x = ed->walls[sc.i].x;
			sc.p_idx = sc.i;
		}
	}
	sector_is_clockwise2(ed, num_sector, &sc);
	if (ed->walls[sc.next_wall_idx].x < ed->walls[sc.prev_wall_idx].x)
		return (1);
	return (0);
}
