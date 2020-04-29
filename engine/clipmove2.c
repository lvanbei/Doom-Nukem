/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipmove2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:40 by hde-moff          #+#    #+#             */
/*   Updated: 2019/11/25 15:52:05 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	clipmove_end_func(t_engine *eng, t_thing *thing, t_clipmove_struct *cm)
{
	int i;

	i = 0;
	while (i < cm->cl.num_clipsects)
	{
		if (inside_sector(eng, cm->x, cm->y, cm->cl.clipsects[i]))
		{
			thing->x = cm->x;
			thing->y = cm->y;
			if (cm->flags & CLIPMOVE_F_PROJ)
				thing->z = cm->z;
			thing->sector = cm->cl.clipsects[i++];
			return (cm->ret);
		}
		i++;
	}
	i = update_thing_sector(eng, thing, cm->x, cm->y);
	if (i != -1)
	{
		thing->x = cm->x;
		thing->y = cm->y;
		thing->sector = i;
		return (cm->ret);
	}
	return (-1);
}
