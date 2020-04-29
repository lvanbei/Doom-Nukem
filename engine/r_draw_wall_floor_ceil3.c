/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_wall_floor_ceil3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	init_draw_ceil(t_plane_thread_info **it_ptr,
		t_draw_plane *dp, void *in)
{
	t_plane_thread_info *it;

	*it_ptr = in;
	it = *it_ptr;
	dp->texture =
		it->r->eng->textures[it->r->eng->sectors[it->pvwall->sect_id].CT];
	dp->info.z = it->d->ceiling_height;
	dp->info.pitch_shift = it->r->eng->player_pitch_shift;
	dp->info.player_x = it->r->eng->player.x;
	dp->info.player_y = it->r->eng->player.y;
	dp->info.rev_sin_ang = it->r->eng->rev_sin_ang;
	dp->info.rev_cos_ang = it->r->eng->rev_cos_ang;
	dp->x1 = it->d->first;
	dp->x2 = it->d->last;
	dp->y1 = it->r->umost[dp->x1];
	dp->y2 = dp->y1;
}

int		draw_ceil_loop1(t_plane_thread_info *it,
		t_draw_plane *dp)
{
	while (dp->y1 < dp->y2 - 1)
	{
		++dp->y1;
		draw_hline((t_draw_line) {it->r, dp->lastx[dp->y1], dp->x,
				dp->y1, dp->texture, &dp->info});
	}
	if (dp->x == dp->x2)
		return (0);
	dp->y1 = it->r->umost[dp->x + 1];
	dp->y2 = dp->y1;
	return (1);
}

void	init_draw_floor(t_plane_thread_info **it_ptr,
		t_draw_plane *dp, void *in)
{
	t_plane_thread_info *it;

	*it_ptr = in;
	it = *it_ptr;
	dp->texture =
		it->r->eng->textures[it->r->eng->sectors[it->pvwall->sect_id].FT];
	dp->info.z = it->d->floor_height;
	dp->info.pitch_shift = it->r->eng->player_pitch_shift;
	dp->info.player_x = it->r->eng->player.x;
	dp->info.player_y = it->r->eng->player.y;
	dp->info.rev_sin_ang = it->r->eng->rev_sin_ang;
	dp->info.rev_cos_ang = it->r->eng->rev_cos_ang;
	dp->x1 = it->d->first;
	dp->x2 = it->d->last;
	dp->y1 = it->d->dwb[dp->x1];
	dp->y2 = dp->y1;
}

int		draw_floor_loop1(t_plane_thread_info *it,
		t_draw_plane *dp)
{
	if (dp->twall >= dp->y2)
	{
		while (dp->y1 < dp->y2 - 1)
		{
			++(dp->y1);
			draw_hline((t_draw_line) {it->r, dp->lastx[dp->y1], dp->x, dp->y1,
					dp->texture, &dp->info});
		}
		dp->y1 = dp->twall;
		return (0);
	}
	return (1);
}
