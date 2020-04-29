/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_shoot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:20:30 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/04 12:46:50 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void		key_shoot(t_engine *eng)
{
	if (eng->p_i.gun_number == 0 && eng->p_i.ammo_per_load_gun !=
			eng->p_i.ammo_gun && eng->p_i.ammo_gun > 0 &&
			!eng->p_i.gun_load_led && eng->p_i.key_hand == 0)
		eng->p_i.shoot_led = 1;
	if (!eng->p_i.gun_load_led && eng->p_i.gun_number == 1 &&
			eng->p_i.key_hand == 0)
	{
		if (eng->p_i.ammo_rpg >= 0)
			eng->p_i.ammo_rpg--;
		eng->p_i.rpg_shoot_led = 1;
		if (eng->p_i.ammo_rpg == -1)
		{
			eng->p_i.rpg_shoot_led = 0;
			eng->p_i.ammo_rpg = 0;
		}
	}
}
