/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_select_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		tl_select_wall2(t_ed *ed, t_tl_select_wall *ts)
{
	int i;

	i = -1;
	while (++i < ed->num_walls)
	{
		ts->w1 = &ed->walls[i];
		ts->w2 = &ed->walls[ts->w1->next_wall];
		ts->tmp = w2p_dist(ts->w1, ts->w2, ts->p_x, ts->p_y);
		if (ts->down && ed->istates.shift_down && i == ed->istates.active_wall)
			continue ;
		if (ts->tmp < ts->dist)
		{
			ts->dist = ts->tmp;
			ts->hit = i;
		}
	}
}

static void		tl_select_wall3(t_ed *ed, t_tl_select_wall *ts)
{
	ed->istates.active_wall = ts->hit;
	ed->istates.active_wall_has_co = 0;
	if (ts->hit != -1)
	{
		if (get_co_wall(ed, ts->hit) != -1)
			ed->istates.active_wall_has_co = 1;
		ed->context_menu[TL_SELECT_WALL].tex_pick_p[TXP_BOT] =
			&ed->walls[ed->istates.active_wall].b_texture;
		ed->context_menu[TL_SELECT_WALL].tex_pick_p[TXP_MAIN] =
			&ed->walls[ed->istates.active_wall].m_texture;
		ed->context_menu[TL_SELECT_WALL].tex_pick_p[TXP_TOP] =
			&ed->walls[ed->istates.active_wall].t_texture;
	}
}

void			tl_select_wall(t_ed *ed, int screen_x, int screen_y, int down)
{
	t_tl_select_wall ts;

	screen_to_map(&ed->view, (t_v2) {screen_x, screen_y}, &ts.p_x, &ts.p_y);
	ts.hit = -1;
	ts.down = down;
	ts.dist = 0.5f;
	ed->istates.hot_wall = ts.hit;
	tl_select_wall2(ed, &ts);
	if (down)
		tl_select_wall3(ed, &ts);
}
