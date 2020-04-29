/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:37 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:34 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void		display_win(t_engine *eng)
{
	if (eng->p_i.win)
	{
		SDL_BlitSurface(eng->p_i.ui_surface[UI_WIN], 0, eng->surface, 0);
	}
}

int			check_mouse_sector(t_engine *eng)
{
	int		i;

	i = -1;
	while (++i < (int)eng->num_things)
		if ((int)eng->player.sector == eng->things[i].sector &&
				(eng->things[i].type == TH_MOUSE_ENDING))
			return (i);
	return (-1);
}

void		win(t_engine *eng, int *game_pause)
{
	int		i;
	double	delta;

	delta = 1.0f;
	i = check_mouse_sector(eng);
	if (i != -1)
		if (eng->player.x >= eng->things[i].x - delta && eng->player.x <=
			eng->things[i].x + delta && eng->player.y >= eng->things[i].y -
			delta && eng->player.y <= eng->things[i].y + delta && eng->player.z
			<= eng->sectors[eng->player.sector].floor_height + 2.0f)
		{
			*game_pause = 1;
			eng->p_i.win = 1;
		}
}
