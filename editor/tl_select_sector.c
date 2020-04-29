/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_select_sector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int			get_parent_co_start_wall(t_ed *ed, t_delete_sector *ds)
{
	ds->i = -1;
	while (++ds->i < ed->num_walls)
	{
		if (ds->i != ds->start_wall && ed->walls[ds->i].x == ds->p_x
				&& ed->walls[ds->i].y == ds->p_y)
		{
			ds->cur0 = ds->start_wall;
			ds->cur1 = ds->i;
			ds->nw = ds->num_walls;
			while (ds->nw--)
			{
				ds->cur0 = ed->walls[ds->cur0].next_wall;
				ds->cur1 = ed->walls[ds->cur1].next_wall;
				if (ed->walls[ds->cur0].x !=
						ed->walls[ds->cur1].x ||
						ed->walls[ds->cur0].y !=
						ed->walls[ds->cur1].y)
					break ;
			}
			if (ds->nw == -1)
				return (ds->i);
		}
	}
	return (-1);
}

static void			parent_prepoc(t_ed *ed, int sect_id,
		t_delete_sector *ds)
{
	if (ds->parent_co_start_wall != -1)
	{
		ds->parent_sect = get_sector(ed, ds->parent_co_start_wall);
		slow_memmove(&ed->walls[ds->parent_co_start_wall],
				&ed->walls[ds->parent_co_start_wall] + ds->num_walls,
				sizeof(t_wall) * (ed->num_walls - (ds->parent_co_start_wall +
						ds->num_walls)));
		ed->num_walls -= ds->num_walls;
		ds->i = -1;
		while (++ds->i < ed->num_walls)
		{
			if (ed->walls[ds->i].next_wall >= ds->parent_co_start_wall)
				ed->walls[ds->i].next_wall -= ds->num_walls;
		}
		ed->sectors[ds->parent_sect].num_walls -= ds->num_walls;
		ds->i = ds->parent_sect;
		while (++ds->i < ed->num_sectors)
			ed->sectors[ds->i].start_wall -= ds->num_walls;
		ds->start_wall = ed->sectors[sect_id].start_wall;
	}
}

static void			delete_sector2(t_ed *ed, int sect_id, t_delete_sector *ds)
{
	if ((ds->start_wall + ds->num_walls) == ed->num_walls)
		ed->num_walls -= ds->num_walls;
	else
	{
		slow_memmove(&ed->walls[ds->start_wall], &ed->walls[ds->start_wall] +
				ds->num_walls, sizeof(t_wall) * (ed->num_walls -
					(ds->start_wall + ds->num_walls)));
		ed->num_walls -= ds->num_walls;
	}
	ds->i = -1;
	while (++ds->i < ed->num_walls)
	{
		if (ed->walls[ds->i].next_wall >= ds->start_wall)
			ed->walls[ds->i].next_wall -= ds->num_walls;
		if (ed->walls[ds->i].next_sector == sect_id)
		{
			ed->walls[ds->i].next_sector = -1;
			ed->walls[ds->i].m_texture = 0;
		}
		if (ed->walls[ds->i].next_sector > sect_id)
			ed->walls[ds->i].next_sector -= 1;
	}
}

static void			delete_sector3(t_ed *ed, int sect_id, t_delete_sector *ds)
{
	if (sect_id == (ed->num_sectors - 1))
		ed->num_sectors -= 1;
	else
	{
		slow_memmove(&ed->sectors[sect_id], &ed->sectors[sect_id] + 1,
				sizeof(t_sector) * (ed->num_sectors - (sect_id + 1)));
		ed->num_sectors -= 1;
	}
	ds->i = sect_id - 1;
	while (++ds->i < ed->num_sectors)
		ed->sectors[ds->i].start_wall -= ds->num_walls;
	ds->i = -1;
	while (++ds->i < ed->num_things)
	{
		if (ed->things[ds->i].sector == sect_id)
			delete_thing(ed, ds->i--);
		if (ed->things[ds->i].sector > sect_id)
			ed->things[ds->i].sector -= 1;
	}
	if (ed->player.sector == sect_id)
		ed->player_set = 0;
}

void				delete_sector(t_ed *ed, int sect_id)
{
	t_delete_sector	ds;

	ds.start_wall = ed->sectors[sect_id].start_wall;
	ds.num_walls = ed->sectors[sect_id].num_walls;
	set_link_prev(ed, ds.start_wall, (ds.start_wall + ds.num_walls) - 1);
	ds.p_x = ed->walls[ds.start_wall].x;
	ds.p_y = ed->walls[ds.start_wall].y;
	ds.parent_co_start_wall = get_parent_co_start_wall(ed, &ds);
	parent_prepoc(ed, sect_id, &ds);
	delete_sector2(ed, sect_id, &ds);
	delete_sector3(ed, sect_id, &ds);
}
