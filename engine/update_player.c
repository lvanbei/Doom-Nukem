/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:52:10 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/04 15:15:09 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline void	update_view(t_engine *eng, const uint8_t *key_states,
		double delta)
{
	int n_pitch_shift;

	n_pitch_shift = 0;
	if (key_states[SDL_SCANCODE_LEFT])
		eng->player.attr.yaw =
			add_angle_wrap(eng->player.attr.yaw + (ARROW_X_RAD_PER_S * delta));
	if (key_states[SDL_SCANCODE_RIGHT])
		eng->player.attr.yaw =
			add_angle_wrap(eng->player.attr.yaw - (ARROW_X_RAD_PER_S * delta));
	if (key_states[SDL_SCANCODE_UP])
	{
		n_pitch_shift = eng->player_pitch_shift + (ARROW_Y_PX_PER_S * delta);
		eng->player_pitch_shift =
			f_clamp(-MAX_PITCH, n_pitch_shift, MAX_PITCH);
	}
	if (key_states[SDL_SCANCODE_DOWN])
	{
		n_pitch_shift = eng->player_pitch_shift + (-ARROW_Y_PX_PER_S * delta);
		eng->player_pitch_shift =
			f_clamp(-MAX_PITCH, n_pitch_shift, MAX_PITCH);
	}
}

static inline void	gravity_func(t_engine *eng, const uint8_t *key_states,
		t_updatep_struct *ps, double delta_t)
{
	ps->jp_available = (eng->p_i.jet_pack_led
			&& eng->p_i.inv_items[UI_ITEM_JET_PACK]) ? 1 : 0;
	if (key_states[SDL_SCANCODE_SPACE] && (ps->on_ground || ps->jp_available))
	{
		if (ps->on_ground)
			ps->zv = JUMP_STARTVELOCITY;
		else if (ps->jp_available)
			ps->zv = JETPACK_THRUST_VELOCITY;
		ps->on_ground = 0;
	}
	else if (key_states[SDL_SCANCODE_LCTRL] && ps->on_ground)
		eng->player_flags |= PF_CROUCH;
	else
		eng->player_flags &= ~PF_CROUCH;
	eng->player.z = eng->player.z + (ps->zv * delta_t * 5);
	ps->zv = ps->zv + (-2 * delta_t * 5);
}

static inline void	compute_vectors(t_engine *eng, const uint8_t *key_states,
		double delta_t, t_v2f *vec)
{
	if (key_states[SDL_SCANCODE_W])
	{
		vec->y += sin(eng->player.attr.yaw) * (METERS_PER_SECOND * delta_t);
		vec->x += cos(eng->player.attr.yaw) * (METERS_PER_SECOND * delta_t);
	}
	if (key_states[SDL_SCANCODE_S])
	{
		vec->y -= sin(eng->player.attr.yaw) * (METERS_PER_SECOND * delta_t);
		vec->x -= cos(eng->player.attr.yaw) * (METERS_PER_SECOND * delta_t);
	}
	if (key_states[SDL_SCANCODE_D])
	{
		vec->y -= sin(eng->player.attr.yaw + M_PI / 2) *
			(METERS_PER_SECOND * delta_t);
		vec->x -= cos(eng->player.attr.yaw + M_PI / 2) *
			(METERS_PER_SECOND * delta_t);
	}
	if (key_states[SDL_SCANCODE_A])
	{
		vec->y += sin(eng->player.attr.yaw + M_PI / 2) *
			(METERS_PER_SECOND * delta_t);
		vec->x += cos(eng->player.attr.yaw + M_PI / 2) *
			(METERS_PER_SECOND * delta_t);
	}
}

static inline void	adjust_floor(t_engine *eng, t_updatep_struct *ps)
{
	if (eng->player_flags & PF_CROUCH)
	{
		eng->player.z = eng->sectors[eng->player.sector].floor_height;
		eng->player.z += PLAYER_HEIGHT34;
	}
	else
	{
		eng->player.z = eng->sectors[eng->player.sector].floor_height;
		eng->player.z += PLAYER_HEIGHT;
	}
	ps->zv = 0;
	ps->on_ground = 1;
}

void				update_player(t_engine *eng, const uint8_t *key_states,
		double delta_t)
{
	static t_updatep_struct	ps = {.on_ground = 1};

	ps.vec.x = 0;
	ps.vec.y = 0;
	update_view(eng, key_states, delta_t);
	compute_vectors(eng, key_states, delta_t, &ps.vec);
	gravity_func(eng, key_states, &ps, delta_t);
	if (eng->player.z + PLAYER_CEILING_CLIP >
			eng->sectors[eng->player.sector].ceiling_height)
	{
		eng->player.z = eng->sectors[eng->player.sector].ceiling_height
			- PLAYER_CEILING_CLIP;
	}
	if (eng->player.z < eng->sectors[eng->player.sector].floor_height
			+ PLAYER_HEIGHT)
	{
		adjust_floor(eng, &ps);
	}
	if (ps.on_ground == 0)
		ps.zv = f_clamp(TERMINAL_VELOCITY, ps.zv, ps.zv);
	clipmove(eng, &eng->player, (t_v3f) {ps.vec.x, ps.vec.y, 0.0f}, 0);
	pushmove(eng, &eng->player, eng->player.sector);
}
