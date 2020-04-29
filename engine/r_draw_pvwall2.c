/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_pvwall2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void					dp_handle_wall(t_render *r, int pvwall_id,
		t_draw_pvwall *dp)
{
	if (dp->d.first <= WIDTH_CENTER && dp->d.last >= WIDTH_CENTER)
	{
		if (r->umost[WIDTH_CENTER] < r->dmost[WIDTH_CENTER])
		{
			dp->yl = dp->d.top_yh_frac + (dp->d.top_yh_step *
					(dp->d.first - dp->pvwall->col0));
			dp->yh = dp->d.bot_yl_frac + (dp->d.bot_yl_step *
					(dp->d.first - dp->pvwall->col0));
			if (dp->yl <= HEIGHT_CENTER && dp->yh >= HEIGHT_CENTER)
			{
				r->eng->pvwall_front = *(dp->pvwall);
				r->eng->wall_in_front = dp->pvwall->wall_id;
			}
		}
	}
	draw_wall_flats(r, dp->pvwall, &dp->d);
	r->clip.smost_walltype[r->clip.num_smost_walls] = SMOSTW_FULL;
	r->clip.smost_wall[r->clip.num_smost_walls] = pvwall_id;
	r->clip.num_smost_walls++;
}

static inline void		dp_handle_portal0(t_render *r, t_draw_pvwall *dp)
{
	if (r->umost[WIDTH_CENTER] < r->dmost[WIDTH_CENTER])
	{
		dp->yl = dp->d.top_yl_frac + (dp->d.top_yl_step * (dp->d.first -
					dp->pvwall->col0));
		dp->yh = dp->d.top_yh_frac + (dp->d.top_yh_step * (dp->d.first -
					dp->pvwall->col0));
		if (dp->yl <= HEIGHT_CENTER && dp->yh >= HEIGHT_CENTER)
		{
			r->eng->pvwall_front = *(dp->pvwall);
			r->eng->wall_in_front = dp->pvwall->wall_id;
		}
		else
		{
			dp->yl = dp->d.bot_yl_frac + (dp->d.bot_yl_step * (dp->d.first -
						dp->pvwall->col0));
			dp->yh = dp->d.bot_yh_frac + (dp->d.bot_yh_step * (dp->d.first -
						dp->pvwall->col0));
			if (dp->yl <= HEIGHT_CENTER && dp->yh >= HEIGHT_CENTER)
			{
				r->eng->pvwall_front = *(dp->pvwall);
				r->eng->wall_in_front = dp->pvwall->wall_id;
			}
		}
	}
}

void					dp_handle_portal(t_render *r, int pvwall_id,
		t_draw_pvwall *dp)
{
	if (dp->d.first <= WIDTH_CENTER && dp->d.last >= WIDTH_CENTER)
		dp_handle_portal0(r, dp);
	if (dp->wall.m_texture != -1)
		draw_door_flats(r, dp->pvwall, &dp->d);
	else
		draw_portal_flats(r, dp->pvwall, &dp->d);
	r->clip.smost_walltype[r->clip.num_smost_walls] = SMOSTW_UP;
	r->clip.smost_wall[r->clip.num_smost_walls] = pvwall_id;
	r->clip.smost_wallstart[r->clip.num_smost_walls] = r->clip.num_smost;
	dp->num = (dp->pvwall->col1 - dp->pvwall->col0) + 1;
	slow_memcpy(&r->clip.smost[r->clip.num_smost],
			&dp->d.tmp_umost[dp->pvwall->col0], sizeof(r->clip.smost[0]) *
			dp->num);
	r->clip.num_smost += dp->num;
	r->clip.num_smost_walls++;
	r->clip.smost_walltype[r->clip.num_smost_walls] = SMOSTW_DOWN;
	r->clip.smost_wall[r->clip.num_smost_walls] = pvwall_id;
	r->clip.smost_wallstart[r->clip.num_smost_walls] = r->clip.num_smost;
	slow_memcpy(&r->clip.smost[r->clip.num_smost],
			&dp->d.tmp_dmost[dp->pvwall->col0], sizeof(r->clip.smost[0]) *
			dp->num);
	r->clip.num_smost += dp->num;
	r->clip.num_smost_walls++;
}

void					update_pvwall_most(t_render *r, t_draw_pvwall *dp)
{
	if (dp->is_portal)
	{
		slow_memcpy(&r->umost[dp->d.first], &dp->d.tmp_umost[dp->d.first],
				(dp->d.last - dp->d.first + 1) * sizeof(r->umost[0]));
		slow_memcpy(&r->dmost[dp->d.first], &dp->d.tmp_dmost[dp->d.first],
				(dp->d.last - dp->d.first + 1) * sizeof(r->dmost[0]));
	}
	else
		slow_memcpy(&r->umost[dp->d.first], &r->dmost[dp->d.first],
				(dp->d.last - dp->d.first + 1) * sizeof(r->umost[0]));
}
