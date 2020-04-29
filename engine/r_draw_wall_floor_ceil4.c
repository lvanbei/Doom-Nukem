/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_wall_floor_ceil4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline void	draw_floor_loop2(t_plane_thread_info *it,
		t_draw_plane *dp)
{
	while (dp->y1 < dp->twall)
	{
		++dp->y1;
		draw_hline((t_draw_line) {it->r, dp->lastx[dp->y1], dp->x, dp->y1,
				dp->texture, &dp->info});
	}
	while (dp->y1 > dp->twall)
		dp->lastx[dp->y1--] = dp->x;
}

static inline void	draw_floor_loop3(t_plane_thread_info *it,
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

static inline int	draw_floor_loop4(t_plane_thread_info *it,
		t_draw_plane *dp)
{
	while (dp->y1 < dp->y2 - 1)
	{
		++(dp->y1);
		draw_hline((t_draw_line) {it->r, dp->lastx[dp->y1], dp->x, dp->y1,
				dp->texture, &dp->info});
	}
	if (dp->x == dp->x2)
		return (0);
	dp->y1 = it->d->dwb[dp->x + 1];
	dp->y2 = dp->y1;
	return (1);
}

static inline void	draw_floor_loop5(t_plane_thread_info *it,
		t_draw_plane *dp)
{
	++(dp->y1);
	draw_hline((t_draw_line) {it->r, dp->lastx[dp->y1], dp->x2, dp->y1,
			dp->texture, &dp->info});
}

void				*draw_floor(void *in)
{
	t_plane_thread_info *it;
	t_draw_plane		dp;

	init_draw_floor(&it, &dp, in);
	dp.x = dp.x1 - 1;
	while (++(dp.x) <= dp.x2)
	{
		dp.twall = it->d->dwb[dp.x] - 1;
		dp.bwall = it->r->dmost[dp.x];
		if (dp.twall < dp.bwall - 1)
		{
			if (draw_floor_loop1(it, &dp))
				draw_floor_loop2(it, &dp);
			draw_floor_loop3(it, &dp);
		}
		else
		{
			if (!draw_floor_loop4(it, &dp))
				break ;
		}
	}
	while (dp.y1 < dp.y2 - 1)
		draw_floor_loop5(it, &dp);
	return (NULL);
}
