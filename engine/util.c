/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	get_sector(t_engine *eng, int wall_id)
{
	int	last_wall;
	int	i;

	i = -1;
	last_wall = 0;
	while (++i < eng->num_sectors)
	{
		last_wall = eng->sectors[i].start_wall + eng->sectors[i].num_walls;
		if (eng->sectors[i].start_wall <= wall_id && wall_id < last_wall)
			return (i);
	}
	abort_error(eng, "couldn't find sector for wall: %d\n", wall_id);
	return (-1);
}
