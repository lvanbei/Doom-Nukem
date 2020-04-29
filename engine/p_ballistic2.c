/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_ballistic2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline int		adjust_wall(t_missile_struct *ms)
{
	if (ms->w.x0 <= 0.0f)
	{
		if (ms->w.x1 <= 0.0f)
		{
			if (ms->w.x0 < ms->w.x1)
				ms->w.x1 = 0.01f;
			else
				ms->w.x0 = 0.01f;
		}
	}
	else
	{
		if (ms->w.x1 > 0.0f)
		{
			if (ms->w.x1 > ms->w.x0)
				ms->w.x0 = -0.01f;
			else
				ms->w.x1 = -0.01f;
		}
	}
	if (get_line_intersection((t_line2f) {0.0f, 0.0f, 0.0f, fmax(ms->w.y0,
					ms->w.y1) + 1.0f}, (t_line2f) {ms->w.x0, ms->w.y0,
				ms->w.x1, ms->w.y1}, &ms->p.x, &ms->p.y) == 0)
		return (-1);
	return (1);
}

static inline void		launch_missile2(t_engine *eng, t_missile_struct *ms)
{
	eng->things[eng->num_things + eng->projectile_queue_idx].x = eng->player.x
		+ (ms->traj.x * PROJECTILE_METERS_PER_SECOND * 0.01f);
	eng->things[eng->num_things + eng->projectile_queue_idx].y = eng->player.y
		+ (ms->traj.y * PROJECTILE_METERS_PER_SECOND * 0.01f);
	eng->things[eng->num_things + eng->projectile_queue_idx].z = eng->player.z
		+ (ms->traj.z * PROJECTILE_METERS_PER_SECOND * 0.01f);
	eng->things[eng->num_things + eng->projectile_queue_idx].type =
		TH_FIREBALL;
	eng->things[eng->num_things + eng->projectile_queue_idx].sector =
		update_thing_sector(eng, &eng->things[eng->num_things +
				eng->projectile_queue_idx],
			eng->things[eng->num_things + eng->projectile_queue_idx].x,
			eng->things[eng->num_things + eng->projectile_queue_idx].y);
	if (eng->num_projectiles < MAX_NUM_PROJECTILES)
		eng->num_projectiles++;
	eng->projectile_queue_idx++;
	if (eng->projectile_queue_idx >= MAX_NUM_PROJECTILES)
		eng->projectile_queue_idx -= MAX_NUM_PROJECTILES;
}

void					launch_missile(t_engine *eng)
{
	t_missile_struct ms;

	ms.w = eng->pvwall_front.playerspace;
	if (get_line_intersection((t_line2f) {0.0f, 0.0f, 0.0f, fmax(ms.w.y0,
					ms.w.y1) + 1.0f}, (t_line2f) {ms.w.x0, ms.w.y0, ms.w.x1,
				ms.w.y1}, &ms.p.x, &ms.p.y) == 0)
	{
		if (adjust_wall(&ms) == -1)
			return ;
	}
	ms.p.z = (ms.p.y * eng->player_pitch_shift) / VSCALE;
	ms.p.y -= 0.1f;
	ms.traj.z = ms.p.z;
	ms.traj.x = ms.p.x * eng->rev_cos_ang - ms.p.y * eng->rev_sin_ang;
	ms.traj.y = ms.p.x * eng->rev_sin_ang + ms.p.y * eng->rev_cos_ang;
	ms.len = sqrt((ms.traj.x * ms.traj.x) + (ms.traj.y * ms.traj.y) +
			(ms.traj.z * ms.traj.z));
	ms.traj.x /= ms.len;
	ms.traj.y /= ms.len;
	ms.traj.z /= ms.len;
	eng->projectile_trajectory[eng->projectile_queue_idx] = ms.traj;
	launch_missile2(eng, &ms);
}
