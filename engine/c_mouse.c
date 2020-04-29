/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_event.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 10:05:32 by hde-moff          #+#    #+#             */
/*   Updated: 2019/10/16 11:01:39 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

double				add_angle_wrap(double a)
{
	if (a > M_PI)
		return (a - (M_PI * 2));
	if (a < -M_PI)
		return (a + (M_PI * 2));
	return (a);
}

static inline void	mouse_motion(t_engine *eng, const SDL_Event *e)
{
	int n_pitch_shift;

	eng->player.attr.yaw = add_angle_wrap(eng->player.attr.yaw -
			(e->motion.xrel * MOUSE_X_RAD_PER_PX));
	n_pitch_shift = eng->player_pitch_shift + (e->motion.yrel *
			-MOUSE_Y_PX_PER_PX);
	eng->PPS = f_clamp(-MAX_PITCH, n_pitch_shift, MAX_PITCH);
}

void				handle_mouse_event(t_engine *eng, const SDL_Event *e)
{
	if (e->type == SDL_MOUSEMOTION)
		mouse_motion(eng, e);
	if (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN
			&& eng->p_i.gun_number == 0 && eng->p_i.ammo_per_load_gun !=
			eng->p_i.ammo_gun && eng->p_i.ammo_gun > 0 &&
			!eng->p_i.gun_load_led && eng->p_i.key_hand == 0)
		eng->p_i.shoot_led = 1;
	if (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN
			&& !eng->p_i.gun_load_led && eng->p_i.gun_number == 1 &&
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
