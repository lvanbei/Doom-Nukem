/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_scansector_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline void	scansector_walls2(t_render *r, t_scansector *sc, int i)
{
	sc->w = r->eng->walls[i];
	sc->w2 = r->eng->walls[sc->w.next_wall];
	sc->l[P].x0 = sc->w.x - r->eng->player.x;
	sc->l[P].y0 = sc->w.y - r->eng->player.y;
	sc->l[P].x1 = sc->w2.x - r->eng->player.x;
	sc->l[P].y1 = sc->w2.y - r->eng->player.y;
	sc->l[ROTATED].x0 = sc->l[P].x0 * r->eng->cos_ang - sc->l[P].y0 *
		r->eng->sin_ang;
	sc->l[ROTATED].y0 = sc->l[P].x0 * r->eng->sin_ang + sc->l[P].y0 *
		r->eng->cos_ang;
	sc->l[ROTATED].x1 = sc->l[P].x1 * r->eng->cos_ang - sc->l[P].y1 *
		r->eng->sin_ang;
	sc->l[ROTATED].y1 = sc->l[P].x1 * r->eng->sin_ang + sc->l[P].y1 *
		r->eng->cos_ang;
}

static inline void	append_to_scansects(t_scansector *sc)
{
	int j;

	j = sc->num_scansects;
	while (--j >= 0)
	{
		if (sc->scansects[j] == sc->w.next_sector)
			break ;
	}
	if (j < 0)
		sc->scansects[sc->num_scansects++] = sc->w.next_sector;
}

static inline void	scansector_walls3(t_render *r, t_scansector *sc, int i)
{
	r->pvwalls[r->num_pvwalls].flags = 0;
	r->pvwalls[r->num_pvwalls].wall_id = i;
	r->pvwalls[r->num_pvwalls].sect_id = sc->scansects[sc->scansect_idx];
	sc->info.flags = &r->pvwalls[r->num_pvwalls].flags;
	sc->info.col0 = &r->pvwalls[r->num_pvwalls].col0;
	sc->info.col1 = &r->pvwalls[r->num_pvwalls].col1;
	sc->info.dist0 = &r->pvwalls[r->num_pvwalls].dist0;
	sc->info.dist1 = &r->pvwalls[r->num_pvwalls].dist1;
	sc->info.playerspace = &r->pvwalls[r->num_pvwalls].playerspace;
	sc->info.screenspace = &r->pvwalls[r->num_pvwalls].screenspace;
}

static inline void	append_to_bunches(t_render *r, t_scansector *sc)
{
	if (!sc->new_bunch &&
			(r->eng->walls[r->pvwalls[r->num_pvwalls - 1].wall_id].next_wall
			== r->pvwalls[r->num_pvwalls].wall_id &&
			r->pvwalls[r->num_pvwalls].col0 >
			r->pvwalls[r->num_pvwalls - 1].col1))
	{
		r->bunches[r->num_bunches].lastx = r->pvwalls[r->num_pvwalls].col1;
		r->bunches[r->num_bunches].last_idx = r->num_pvwalls;
	}
	else
	{
		r->num_bunches++;
		r->bunches[r->num_bunches].firstx = r->pvwalls[r->num_pvwalls].col0;
		r->bunches[r->num_bunches].lastx = r->pvwalls[r->num_pvwalls].col1;
		r->bunches[r->num_bunches].first_idx = r->num_pvwalls;
		r->bunches[r->num_bunches].last_idx = r->num_pvwalls;
		sc->new_bunch = 0;
	}
	r->num_pvwalls++;
}

void				scansector_walls(t_render *r, t_scansector *sc)
{
	int i;

	i = r->eng->sectors[sc->scansects[sc->scansect_idx]].start_wall;
	sc->end_wall = i +
		r->eng->sectors[sc->scansects[sc->scansect_idx]].num_walls;
	while (i < sc->end_wall)
	{
		scansector_walls2(r, sc, i);
		if (((-sc->l[ROTATED].x0 * (sc->l[ROTATED].y1 - sc->l[ROTATED].y0)) +
					(-sc->l[ROTATED].y0 * -(sc->l[ROTATED].x1 -
											sc->l[ROTATED].x0)) < 0) ||
				(sc->l[ROTATED].y0 < 0.0f && sc->l[ROTATED].y1 < 0.0f))
		{
			i++;
			continue;
		}
		if (sc->w.next_sector != -1)
			append_to_scansects(sc);
		scansector_walls3(r, sc, i);
		if (viewspace_clip_transform(&sc->l[ROTATED], &sc->info) == 1)
			append_to_bunches(r, sc);
		i++;
	}
}
