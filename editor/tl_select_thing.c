/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_select_thing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		delete_thing(t_ed *ed, int thing_id)
{
	if (thing_id == -2)
		ed->player_set = 0;
	else
	{
		if (thing_id == (ed->num_things - 1))
			ed->num_things--;
		else
		{
			slow_memmove(&ed->things[thing_id], &ed->things[thing_id] + 1,
					sizeof(t_thing) * ((ed->num_things - 1) - thing_id));
			ed->num_things--;
		}
	}
}

void		delete_active_thing(void *a)
{
	t_ed *ed;

	ed = (t_ed *)a;
	delete_thing(ed, ed->istates.active_thing);
	ed->istates.active_thing = -1;
}

void		tl_select_thing(t_ed *ed, int screen_x, int screen_y)
{
	double	p_x;
	double	p_y;
	int		i;

	screen_to_map(&ed->view, (t_v2) {screen_x, screen_y}, &p_x, &p_y);
	i = -1;
	while (++i < ed->num_things)
	{
		if (sqrt(dist2(ed->things[i].x, ed->things[i].y, p_x, p_y)) < 0.5f)
		{
			ed->istates.active_thing = i;
			ed->context_menu[TL_SELECT_THING].var_control[0] =
				&ed->things[i].attr.yaw;
			return ;
		}
	}
	if (ed->player_set && sqrt(dist2(ed->player.x, ed->player.y, p_x, p_y))
			< 0.5f)
	{
		ed->istates.active_thing = -2;
		ed->context_menu[TL_SELECT_THING].var_control[0] =
			&ed->player.attr.yaw;
		return ;
	}
	ed->istates.active_thing = -1;
}
