/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_guard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:07:38 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/25 10:09:26 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void				thing_update_checks(t_ed *ed)
{
	int i;

	i = -1;
	while (++i < ed->num_things)
		ed->things[i].z = ed->sectors[ed->things[i].sector].floor_height +
			ed->thing_height[ed->things[i].type];
}

static inline void	update_check_door(t_ed *ed, t_wall_update_c w)
{
	w.wall2 = get_co_wall(ed, w.i);
	if (w.wall2 == -1)
		abort_error(ed, "portal: %d had no corresponding opposite portal\n",
				w.i);
	w.sect1 = get_sector(ed, w.i);
	if (ed->walls[w.wall2].next_sector != w.sect1)
		abort_error(ed,
				"portal: %d (corresponding wall: %d) next_sector(%d) not"
				" matching\n", w.i, w.wall2, ed->walls[w.wall2].next_sector);
	if (ed->walls[w.wall2].m_texture == -1)
		ed->walls[w.wall2].m_texture = 0;
	w.sect2 = get_sector(ed, w.wall2);
	w.max_height = fmax(ed->sectors[w.sect1].floor_height,
			ed->sectors[w.sect2].floor_height);
	ed->walls[w.i].door_height = w.max_height;
	ed->walls[w.wall2].door_height = w.max_height;
	ed->walls[w.i].flags = WALL_FLAG_CLOSED;
	ed->walls[w.wall2].flags = WALL_FLAG_CLOSED;
	w.wall_status[w.wall2] = 1;
}

static inline int	update_check_portal(t_ed *ed, t_wall_update_c w)
{
	if (ed->walls[w.i].b_texture == -1)
	{
		ft_printf("wall: %d no bottom texture; set to 0\n", w.i);
		ed->walls[w.i].b_texture = 0;
	}
	if (ed->walls[w.i].t_texture == -1)
	{
		ft_printf("wall: %d no top texture; set to 0\n", w.i);
		ed->walls[w.i].t_texture = 0;
	}
	if (ed->walls[w.i].m_texture != -1)
	{
		if (w.wall_status[w.i] == 1)
		{
			++w.i;
			return (0);
		}
		update_check_door(ed, w);
		return (1);
	}
	ed->walls[w.i].flags = WALL_FLAG_OPEN;
	return (1);
}

void				wall_update_checks(t_ed *ed)
{
	t_wall_update_c		w;

	slow_bzero(&w.wall_status, MAX_WALLS);
	w.i = -1;
	while (++w.i < ed->num_walls)
	{
		if (ed->walls[w.i].next_sector == -1)
		{
			if (ed->walls[w.i].m_texture == -1)
			{
				ft_printf("wall: %d no texture; set to 0\n", w.i);
				ed->walls[w.i].m_texture = 0;
			}
		}
		else
		{
			if (!update_check_portal(ed, w))
				continue ;
		}
		++w.i;
	}
}
