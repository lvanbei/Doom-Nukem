/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_select_wall2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		toggle_portal2(t_ed *ed, int wall_id, int w2)
{
	int sect1;
	int sect2;

	sect1 = get_sector(ed, w2);
	sect2 = get_sector(ed, wall_id);
	ed->walls[wall_id].next_sector = sect1;
	ed->walls[w2].next_sector = sect2;
	ed->walls[wall_id].m_texture = -1;
	ed->walls[w2].m_texture = -1;
}

void		toggle_portal(t_ed *ed, int wall_id)
{
	int w2;

	w2 = get_co_wall(ed, wall_id);
	if (w2 == -1)
		return ;
	if (ed->walls[wall_id].next_sector != -1)
	{
		ed->walls[wall_id].next_sector = -1;
		ed->walls[wall_id].m_texture = ed->tl_w.default_m_texture;
		ed->walls[w2].next_sector = -1;
		ed->walls[w2].m_texture = ed->tl_w.default_m_texture;
	}
	else
		toggle_portal2(ed, wall_id, w2);
}

void		toggle_portal_active_wall(void *a)
{
	t_ed *ed;

	ed = (t_ed *)a;
	toggle_portal(ed, ed->istates.active_wall);
}

void		gather_walls(t_ed *ed, int screen_x, int screen_y)
{
	int		j;
	int		i;
	double	p_x;
	double	p_y;

	screen_to_map_round(&ed->view, (t_v2) {screen_x, screen_y}, &p_x, &p_y);
	j = 0;
	i = -1;
	while (++i < ed->num_walls)
		if (ed->walls[i].x == p_x && ed->walls[i].y == p_y)
			ed->tl_selected_walls[j++] = &ed->walls[i];
}

void		release_walls(t_ed *ed, int screen_x, int screen_y)
{
	int		i;
	int		w;
	double	p_x;
	double	p_y;

	screen_to_map_round(&ed->view, (t_v2) {screen_x, screen_y}, &p_x, &p_y);
	i = 0;
	while (ed->tl_selected_walls[i])
	{
		w = -1;
		while (++w < ed->num_walls)
			if (ed->walls[w].x == p_x && ed->walls[w].y == p_y)
				return ;
		i++;
	}
	i = 0;
	while (ed->tl_selected_walls[i])
	{
		ed->tl_selected_walls[i]->x = p_x;
		ed->tl_selected_walls[i]->y = p_y;
		ed->tl_selected_walls[i] = NULL;
		i++;
	}
}
