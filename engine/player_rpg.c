/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rpg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:46 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:42 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void				rpg_display_shoot(t_engine *eng, t_player_items *p_i,
int delta)
{
	static int		timer = -100;

	if (!eng->p_i.change_gun_led && p_i->gun_number && !p_i->key_hand)
	{
		SDL_BlitSurface(p_i->ui_surface[UI_RPG_1], NULL,
		eng->surface, &p_i->ui_rect[UI_RECT_RPG_1]);
		if (p_i->rpg_shoot_led == 1 && p_i->ammo_rpg >= 0)
		{
			if (timer <= 0)
				SDL_BlitSurface(p_i->ui_surface[UI_RPG_2], NULL,
				eng->surface, &p_i->ui_rect[UI_RECT_RPG_2]);
			if (timer > 0)
				SDL_BlitSurface(p_i->ui_surface[UI_RPG_3], NULL,
				eng->surface, &p_i->ui_rect[UI_RECT_RPG_3]);
			timer += delta;
			if (timer >= 100 || p_i->ammo_rpg < 0)
			{
				timer = -100;
				launch_missile(eng);
				p_i->rpg_shoot_led = 0;
			}
		}
	}
}
