/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_clip_sprite2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline int	clipsprite_full(t_draw_sprite *ds)
{
	if (ds->start_x <= ds->end_x)
	{
		if (ds->start_x == ds->x0 && ds->end_x == ds->x1)
			return (0);
		slow_bzero(&ds->dmost[ds->start_x], (ds->end_x - ds->start_x + 1) *
				sizeof(ds->dmost[0]));
	}
	return (1);
}

static inline void	clipsprite_up(t_render *r, t_draw_sprite *ds, int i, int j)
{
	int x;

	ds->smost_start = r->clip.smost_wallstart[i] - r->pvwalls[j].col0;
	x = ds->start_x - 1;
	while (++x <= ds->end_x)
	{
		if (ds->umost[x] < r->clip.smost[ds->smost_start + x])
			ds->umost[x] = r->clip.smost[ds->smost_start + x];
	}
}

static inline void	clipsprite_down(t_render *r, t_draw_sprite *ds,
		int i, int j)
{
	int x;

	ds->smost_start = r->clip.smost_wallstart[i] - r->pvwalls[j].col0;
	x = ds->start_x - 1;
	while (++x <= ds->end_x)
	{
		if (ds->dmost[x] > r->clip.smost[ds->smost_start + x])
			ds->dmost[x] = r->clip.smost[ds->smost_start + x];
	}
}

int					clipsprite_most(t_render *r, t_draw_sprite *ds, int i,
		int j)
{
	if (r->clip.smost_walltype[i] == SMOSTW_FULL)
	{
		if (!clipsprite_full(ds))
			return (0);
	}
	else if (r->clip.smost_walltype[i] == SMOSTW_UP)
		clipsprite_up(r, ds, i, j);
	else if (r->clip.smost_walltype[i] == SMOSTW_DOWN)
		clipsprite_down(r, ds, i, j);
	return (1);
}
