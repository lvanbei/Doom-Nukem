/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_pvwall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline int		dp_func0(t_render *r, int pvwall_id, t_draw_pvwall *dp,
		double pz)
{
	dp->pvwall = &r->pvwalls[pvwall_id];
	dp->d.first = dp->pvwall->col0;
	dp->d.last = dp->pvwall->col1;
	while (r->umost[dp->d.first] == r->dmost[dp->d.first])
		dp->d.first++;
	if (dp->d.first > dp->d.last)
		return (0);
	while (r->umost[dp->d.last] == r->dmost[dp->d.last])
		dp->d.last--;
	if (dp->d.first > dp->d.last)
		return (0);
	dp->d.s_wall_width = (dp->pvwall->col1 - dp->pvwall->col0) + 1;
	dp->wall = r->eng->walls[dp->pvwall->wall_id];
	dp->is_portal = (dp->wall.next_sector != -1) ? 1 : 0;
	dp->scale0 = R_WALL_HEIGHT / dp->pvwall->dist0;
	dp->scale1 = R_WALL_HEIGHT / dp->pvwall->dist1;
	dp->d.ceiling_height = r->eng->sectors[dp->pvwall->sect_id].CH - pz;
	if (dp->is_portal)
	{
		dp->nyceil = r->eng->sectors[dp->wall.next_sector].CH - pz;
		dp->d.top_height = (dp->d.ceiling_height - dp->nyceil);
	}
	else
		dp->d.top_height = -1;
	return (1);
}

static inline void		dp_func1(t_render *r, t_draw_pvwall *dp,
		double pz)
{
	dp->top0_yl = WIN_HEIGHT / 2 - (dp->d.CH * dp->scale0) + r->eng->PPS;
	dp->top1_yl = WIN_HEIGHT / 2 - (dp->d.CH * dp->scale1) + r->eng->PPS;
	if (dp->d.top_height > 0)
	{
		dp->top0_yh = WIN_HEIGHT / 2 - (dp->nyceil * dp->scale0) + r->eng->PPS;
		dp->top1_yh = WIN_HEIGHT / 2 - (dp->nyceil * dp->scale1) + r->eng->PPS;
	}
	else
	{
		dp->top0_yh = dp->top0_yl;
		dp->top1_yh = dp->top1_yl;
	}
	dp->d.top_yl_step = (dp->top1_yl - dp->top0_yl) / dp->d.s_wall_width;
	dp->d.top_yh_step = (dp->top1_yh - dp->top0_yh) / dp->d.s_wall_width;
	dp->d.floor_height = r->eng->sectors[dp->pvwall->sect_id].floor_height - pz;
	if (dp->is_portal)
	{
		dp->nyfloor = r->eng->sectors[dp->wall.next_sector].floor_height - pz;
		dp->d.bot_height = (dp->nyfloor - dp->d.floor_height);
	}
	else
		dp->d.bot_height = -1;
	dp->bot0_yh = WIN_HEIGHT / 2 - (dp->d.FH * dp->scale0) + r->eng->PPS;
	dp->bot1_yh = WIN_HEIGHT / 2 - (dp->d.FH * dp->scale1) + r->eng->PPS;
}

static inline void		dp_func2(t_render *r, t_draw_pvwall *dp)
{
	if (dp->d.bot_height > 0)
	{
		dp->bot0_yl = WIN_HEIGHT / 2 - (dp->nyfloor * dp->scale0)
			+ r->eng->PPS;
		dp->bot1_yl = WIN_HEIGHT / 2 - (dp->nyfloor * dp->scale1)
			+ r->eng->PPS;
	}
	else
	{
		dp->bot0_yl = dp->bot0_yh;
		dp->bot1_yl = dp->bot1_yh;
	}
	dp->d.bot_yl_step = (dp->bot1_yl - dp->bot0_yl) / dp->d.s_wall_width;
	dp->d.bot_yh_step = (dp->bot1_yh - dp->bot0_yh) / dp->d.s_wall_width;
}

static inline void		dp_func3(t_render *r, t_draw_pvwall *dp,
		double pz)
{
	dp->d.door_height = dp->wall.door_height - pz;
	dp->mid0 = WIN_HEIGHT / 2 - (dp->d.door_height * dp->scale0) + r->eng->PPS;
	dp->mid1 = WIN_HEIGHT / 2 - (dp->d.door_height * dp->scale1) + r->eng->PPS;
	dp->d.mid_step = (dp->mid1 - dp->mid0) / dp->d.s_wall_width;
	if (dp->d.first == dp->d.last && dp->pvwall->dist0 > dp->pvwall->dist1)
	{
		dp->d.top_yl_frac = dp->top1_yl;
		dp->d.top_yh_frac = dp->top1_yh;
		dp->d.mid_frac = dp->mid1;
		dp->d.bot_yl_frac = dp->bot1_yl;
		dp->d.bot_yh_frac = dp->bot1_yh;
	}
	else
	{
		dp->d.top_yl_frac = dp->top0_yl + (dp->d.top_yl_step *
				(dp->d.first - dp->pvwall->col0));
		dp->d.top_yh_frac = dp->top0_yh + (dp->d.top_yh_step *
				(dp->d.first - dp->pvwall->col0));
		dp->d.mid_frac = dp->mid0 + (dp->d.mid_step *
				(dp->d.first - dp->pvwall->col0));
		dp->d.bot_yl_frac = dp->bot0_yl + (dp->d.bot_yl_step
				* (dp->d.first - dp->pvwall->col0));
		dp->d.bot_yh_frac = dp->bot0_yh + (dp->d.bot_yh_step
				* (dp->d.first - dp->pvwall->col0));
	}
}

void					draw_pvwall(t_render *r, int pvwall_id)
{
	t_draw_pvwall			dp;
	t_plane_thread_info		info;

	if (!dp_func0(r, pvwall_id, &dp, r->eng->player.z))
		return ;
	dp_func1(r, &dp, r->eng->player.z);
	dp_func2(r, &dp);
	dp_func3(r, &dp, r->eng->player.z);
	if (!dp.is_portal)
		dp_handle_wall(r, pvwall_id, &dp);
	else
		dp_handle_portal(r, pvwall_id, &dp);
	info = (t_plane_thread_info) {.r = r, .pvwall = dp.pvwall, .d = &dp.d};
	pthread_create(&r->eng->threads[0], NULL, draw_floor, (void *)&info);
	pthread_create(&r->eng->threads[1], NULL, draw_ceil, (void *)&info);
	pthread_join(r->eng->threads[0], NULL);
	pthread_join(r->eng->threads[1], NULL);
	update_pvwall_most(r, &dp);
}
