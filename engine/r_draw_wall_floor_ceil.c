/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_wall_floor_ceil.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline void	draw_ceil_loop2(t_plane_thread_info *it,
		t_draw_plane *dp)
{
	while (dp->y1 < dp->twall)
	{
		++(dp->y1);
		draw_hline((t_draw_line) {it->r, dp->lastx[dp->y1], dp->x, dp->y1,
				dp->texture, &dp->info});
	}
	while (dp->y1 > dp->twall)
		dp->lastx[dp->y1--] = dp->x;
}

static inline void	draw_ceil_loop3(t_plane_thread_info *it,
		t_draw_plane *dp)
{
	while (dp->y2 > dp->bwall)
	{
		--(dp->y2);
		draw_hline((t_draw_line) {it->r, dp->lastx[dp->y2], dp->x, dp->y2,
				dp->texture, &dp->info});
	}
	while (dp->y2 < dp->bwall)
		dp->lastx[dp->y2++] = dp->x;
}

static inline int	draw_ceil_loop4(t_plane_thread_info *it,
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

static inline void	draw_ceil_loop5(t_plane_thread_info *it,
		t_draw_plane *dp)
{
	++(dp->y1);
	draw_hline((t_draw_line) {it->r, dp->lastx[dp->y1], dp->x2, dp->y1,
			dp->texture, &dp->info});
}

void				*draw_ceil(void *in)
{
	t_plane_thread_info	*it;
	t_draw_plane		dp;

	init_draw_ceil(&it, &dp, in);
	dp.x = dp.x1 - 1;
	while (++(dp.x) <= dp.x2)
	{
		dp.twall = it->r->umost[dp.x] - 1;
		dp.bwall = it->d->upwb[dp.x];
		if (dp.twall < dp.bwall - 1)
		{
			if (draw_ceil_loop4(it, &dp))
				draw_ceil_loop2(it, &dp);
			draw_ceil_loop3(it, &dp);
		}
		else
		{
			if (!draw_ceil_loop1(it, &dp))
				break ;
		}
	}
	while (dp.y1 < dp.y2 - 1)
		draw_ceil_loop5(it, &dp);
	return (NULL);
}
