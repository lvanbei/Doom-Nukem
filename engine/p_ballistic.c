/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_ballistic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline t_v3f		create_vec(t_engine *eng, int thing_id, double f_delta)
{
	return ((t_v3f) {eng->projectile_trajectory[thing_id - eng->num_things].x *
		(PROJECTILE_METERS_PER_SECOND * f_delta),
			eng->projectile_trajectory[thing_id - eng->num_things].y *
				(PROJECTILE_METERS_PER_SECOND * f_delta),
			eng->projectile_trajectory[thing_id - eng->num_things].z *
				(PROJECTILE_METERS_PER_SECOND * f_delta)});
}

static inline void		collide_with_monster(t_engine *eng, int thing_id,
		int coll)
{
	eng->things[coll].attr.health -= eng->fireball_damage;
	Mix_PlayChannel(-1, eng->p_i.ui_sound[UI_SOUND_EXPLODE], 0);
	if (eng->things[coll].attr.health <= 0.0f)
	{
		Mix_PlayChannel(-1, eng->p_i.ui_sound[UI_SOUND_DIE], 0);
		eng->things[coll].z = eng->sectors[eng->things[coll].sector].FH
			+ DEADMONSTER_HEIGHT;
		eng->things[coll].type = TH_DEADMONSTER;
	}
	eng->things[thing_id].type = TH_NONE;
}

void					update_projectile(t_engine *eng, int thing_id,
		double f_delta)
{
	int		coll;
	t_v3f	v;

	v = create_vec(eng, thing_id, f_delta);
	coll = clipmove(eng, &eng->things[thing_id], v, CLIPMOVE_F_PROJ);
	if (eng->things[thing_id].z <=
			eng->sectors[eng->things[thing_id].sector].floor_height
			|| eng->things[thing_id].z >=
			eng->sectors[eng->things[thing_id].sector].ceiling_height)
	{
		Mix_PlayChannel(-1, eng->p_i.ui_sound[UI_SOUND_EXPLODE], 0);
		eng->things[thing_id].type = TH_NONE;
		return ;
	}
	if (coll == -2)
		;
	else if (coll == -1)
	{
		Mix_PlayChannel(-1, eng->p_i.ui_sound[UI_SOUND_EXPLODE], 0);
		eng->things[thing_id].type = TH_NONE;
	}
	else
		collide_with_monster(eng, thing_id, coll);
}

static inline void		shoot_bullet2(t_engine *eng, t_bullet_struct *bs)
{
	bs->world.z = bs->p.z + eng->player.z;
	bs->world.x = bs->p.x * eng->rev_cos_ang - bs->p.y * eng->rev_sin_ang;
	bs->world.y = bs->p.x * eng->rev_sin_ang + bs->p.y * eng->rev_cos_ang;
	bs->world.x += eng->player.x;
	bs->world.y += eng->player.y;
	eng->things[eng->num_things + eng->projectile_queue_idx].x = bs->world.x;
	eng->things[eng->num_things + eng->projectile_queue_idx].y = bs->world.y;
	eng->things[eng->num_things + eng->projectile_queue_idx].z = bs->world.z;
	eng->things[eng->num_things + eng->projectile_queue_idx].type = TH_IMPACT;
	eng->things[eng->num_things + eng->projectile_queue_idx].sector =
		get_sector(eng, eng->wall_in_front);
	if (eng->num_projectiles < MAX_NUM_PROJECTILES)
		eng->num_projectiles++;
	eng->projectile_queue_idx++;
	if (eng->projectile_queue_idx >= MAX_NUM_PROJECTILES)
		eng->projectile_queue_idx -= MAX_NUM_PROJECTILES;
}

void					shoot_bullet(t_engine *eng)
{
	t_bullet_struct	bs;

	if (eng->monster_in_front != -1)
	{
		eng->things[eng->monster_in_front].attr.health -= eng->bullet_damage;
		if (eng->things[eng->monster_in_front].attr.health <= 0.0f)
		{
			eng->things[eng->monster_in_front].z =
				eng->sectors[eng->things[eng->monster_in_front].sector].FH +
				DEADMONSTER_HEIGHT;
			Mix_PlayChannel(-1, eng->p_i.ui_sound[UI_SOUND_DIE], 0);
			eng->things[eng->monster_in_front].type = TH_DEADMONSTER;
		}
	}
	else if (eng->wall_in_front != -1)
	{
		bs.w = eng->pvwall_front.playerspace;
		if (get_line_intersection((t_line2f) {0.0f, 0.0f, 0.0f,
					fmax(bs.w.y0, bs.w.y1)}, (t_line2f) {bs.w.x0, bs.w.y0,
					bs.w.x1, bs.w.y1}, &bs.p.x, &bs.p.y) == 0)
			return ;
		bs.p.z = (bs.p.y * eng->player_pitch_shift) / VSCALE;
		bs.p.y -= 0.1f;
		shoot_bullet2(eng, &bs);
	}
}
