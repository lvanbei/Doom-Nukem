/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_clip_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline int		no_conflict(t_render *r, t_draw_sprite *ds,
		int sprite_id, int j)
{
	if (r->pvwalls[j].col0 > ds->x1 || r->pvwalls[j].col1 < ds->x0)
		return (1);
	if (r->pvwalls[j].dist0 >= ds->pvsprite->p.y && r->pvwalls[j].dist1 >=
			ds->pvsprite->p.y)
		return (1);
	if (!sprite_wall_front(r, sprite_id, j))
		return (1);
	return (0);
}

int						clipsprite(t_render *r, int sprite_id,
		t_draw_sprite *ds)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < r->clip.num_smost_walls)
	{
		j = r->clip.smost_wall[i];
		if (no_conflict(r, ds, sprite_id, j))
			continue ;
		ds->start_x = i_max(ds->x0, r->pvwalls[j].col0);
		ds->end_x = i_min(ds->x1, r->pvwalls[j].col1);
		if (!clipsprite_most(r, ds, i, j))
			return (0);
	}
	i = ds->x0 - 1;
	while (++i <= ds->x1)
	{
		if (ds->umost[i] < ds->dmost[i])
			break ;
	}
	if (i - 1 == ds->x1)
		return (0);
	return (1);
}
