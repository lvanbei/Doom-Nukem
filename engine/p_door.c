/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_door.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline void	door_opening_func(t_engine *eng, double f_delta)
{
	eng->walls[eng->doors_opening[0]].door_height +=
		DOOR_METER_PER_S * f_delta;
	eng->walls[eng->doors_opening[1]].door_height +=
		DOOR_METER_PER_S * f_delta;
	if (eng->walls[eng->doors_opening[0]].door_height >=
			eng->door_bounds[1])
	{
		eng->walls[eng->doors_opening[0]].door_height = eng->door_bounds[1];
		eng->walls[eng->doors_opening[1]].door_height = eng->door_bounds[1];
		eng->walls[eng->doors_opening[0]].flags = WALL_FLAG_OPEN;
		eng->walls[eng->doors_opening[1]].flags = WALL_FLAG_OPEN;
		eng->doors_opening[0] = -1;
		eng->doors_opening[1] = -1;
	}
}

void				update_doors(t_engine *eng, double f_delta)
{
	if (eng->doors_opening[0] == -1)
		return ;
	if (eng->door_state == DS_OPENING)
		door_opening_func(eng, f_delta);
	else if (eng->door_state == DS_CLOSING)
	{
		eng->walls[eng->doors_opening[0]].door_height -=
			DOOR_METER_PER_S * f_delta;
		eng->walls[eng->doors_opening[1]].door_height -=
			DOOR_METER_PER_S * f_delta;
		if (eng->walls[eng->doors_opening[0]].door_height <=
				eng->door_bounds[0])
		{
			eng->walls[eng->doors_opening[0]].door_height = eng->door_bounds[0];
			eng->walls[eng->doors_opening[1]].door_height = eng->door_bounds[0];
			eng->walls[eng->doors_opening[0]].flags = WALL_FLAG_CLOSED;
			eng->walls[eng->doors_opening[1]].flags = WALL_FLAG_CLOSED;
			eng->doors_opening[0] = -1;
			eng->doors_opening[1] = -1;
		}
	}
}
