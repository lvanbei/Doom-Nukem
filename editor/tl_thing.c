/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_thing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		set_player(t_ed *ed, double p_x, double p_y, int i)
{
	ed->player.x = p_x;
	ed->player.y = p_y;
	ed->player.z = ed->sectors[i].floor_height + PLAYER_HEIGHT + 0.5f;
	ed->player.sector = i;
	ed->player.attr.yaw = ed->istates.tl_thing_default_yaw;
	ed->player.type = TH_PLAYER;
	ed->player_set = 1;
}

static void		set_thing(t_ed *ed, double p_x, double p_y, int i)
{
	if (ed->num_things >= MAX_THINGS)
		abort_error(ed, "too many things in map\n");
	ed->things[ed->num_things].x = p_x;
	ed->things[ed->num_things].y = p_y;
	ed->things[ed->num_things].z = ed->sectors[i].floor_height +
		ed->thing_height[ed->istates.th_active];
	ed->things[ed->num_things].sector = i;
	if (ed->istates.th_active == TH_MONSTER)
		ed->things[ed->num_things].attr.health = MONSTER_HEALTH;
	else
		ed->things[ed->num_things].attr.yaw = ed->istates.tl_thing_default_yaw;
	ed->things[ed->num_things].type = ed->istates.th_active;
	ed->things[ed->num_things].zv = 0.0f;
	ed->num_things++;
}

void			tl_thing(t_ed *ed, int screen_x, int screen_y)
{
	double	p_x;
	double	p_y;
	int		i;

	screen_to_map(&ed->view, (t_v2) {screen_x, screen_y}, &p_x, &p_y);
	i = -1;
	while (++i < ed->num_sectors)
	{
		if (inside_sector(ed, p_x, p_y, i))
		{
			if (ed->istates.th_active == TH_PLAYER)
				set_player(ed, p_x, p_y, i);
			else
				set_thing(ed, p_x, p_y, i);
			return ;
		}
	}
}
