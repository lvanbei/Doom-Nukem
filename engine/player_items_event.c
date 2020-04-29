/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_items_event.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:11:51 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/04 18:12:04 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void				player_items_event(t_engine *eng, SDL_Event *e)
{
	t_player_items	*p_i;

	p_i = &eng->p_i;
	if (eng->key_states[SDL_SCANCODE_G] && e->type == SDL_KEYDOWN &&
			e->key.repeat == 0 && p_i->inv_items[UI_ITEM_KEY] == 1 &&
			!p_i->change_gun_led)
		p_i->key_hand = 1;
	if (eng->key_states[SDL_SCANCODE_R] && p_i->ammo_gun > 0 && !p_i->key_hand
	&& !p_i->gun_number)
		p_i->gun_load_led = 1;
	if (eng->key_states[SDL_SCANCODE_C] && p_i->key_hand == 0)
	{
		p_i->change_gun_led = 1;
		p_i->gun_load_led = 0;
		p_i->rpg_shoot_led = 0;
		p_i->shoot_led = 0;
	}
	if (eng->key_states[SDL_SCANCODE_F] && e->type ==
			SDL_KEYDOWN && e->key.repeat == 0)
		p_i->item_led = 1;
}
