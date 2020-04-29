/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_things.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:40 by hde-moff          #+#    #+#             */
/*   Updated: 2019/11/25 15:52:05 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	update_things(t_engine *eng, double f_delta)
{
	int i;

	i = 0;
	while (i < eng->num_things + eng->num_projectiles)
	{
		if (eng->things[i].type == TH_MONSTER)
			update_monster(eng, i, f_delta);
		if (eng->things[i].type == TH_FIREBALL)
			update_projectile(eng, i, f_delta);
		i++;
	}
}
