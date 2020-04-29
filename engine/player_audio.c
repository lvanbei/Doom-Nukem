/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_audio.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:16:54 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:07 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void			ui_audio_2(t_player_items *p_i, int *led_3)
{
	if (p_i->rpg_shoot_led == 1 && *led_3 == 1)
	{
		Mix_PlayChannel(-1, p_i->ui_sound[UI_SOUND_RPG_SHOOT], 0);
		*led_3 = 0;
	}
	if (p_i->rpg_shoot_led == 0)
		*led_3 = 1;
}

void				ui_audio(t_player_items *p_i)
{
	static int		led = 1;
	static int		led_2 = 1;
	static int		led_3 = 1;

	if (p_i->find_item_led == 1)
		Mix_PlayChannel(-1, p_i->ui_sound[UI_SOUND_GET_ITEM], 0);
	if (p_i->shoot_led == 1 && led == 1)
	{
		Mix_PlayChannel(-1, p_i->ui_sound[UI_SOUND_GUN_SHOOT], 0);
		led = 0;
	}
	if (p_i->shoot_led == 0)
		led = 1;
	if ((p_i->gun_load_led == 1 || p_i->ammo_per_load_gun == p_i->ammo_gun)
			&& p_i->shoot_led == 0 && led_2 == 1 && p_i->gun_number == 0)
	{
		Mix_PlayChannel(-1, p_i->ui_sound[UI_SOUND_GUN_RELOAD_1], 0);
		led_2 = 0;
	}
	if (p_i->gun_load_led == 0 && p_i->ammo_per_load_gun != p_i->ammo_gun)
		led_2 = 1;
	ui_audio_2(p_i, &led_3);
}

void				menu_audio(int delta, t_engine *eng)
{
	static int	timer_audio = 0;

	if (timer_audio == 0)
		Mix_PlayChannel(-1, eng->p_i.ui_sound[UI_SOUND_MENU], 0);
	timer_audio += delta;
	if (timer_audio >= 28500)
		timer_audio = 0;
}
