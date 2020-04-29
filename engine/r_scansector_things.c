/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_scansector_things.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline void	scansector_things3(t_render *r, t_scansector *sc,
		t_scanthing *st)
{
	if (((-st->px * cos(st->thing_ang)) + (-st->py * sin(st->thing_ang))) < 0)
		st->thing_ang -= M_PI;
	st->xv = cos(st->thing_ang + M_PI / 2) *
		(r->eng->thing_width[st->type] / 2.0f);
	st->yv = sin(st->thing_ang + M_PI / 2) *
		(r->eng->thing_width[st->type] / 2.0f);
	sc->l[ROTATED].x0 = st->px - st->xv;
	sc->l[ROTATED].y0 = st->py - st->yv;
	sc->l[ROTATED].x1 = st->px + st->xv;
	sc->l[ROTATED].y1 = st->py + st->yv;
}

static inline void	scansector_things2(t_render *r, t_scanthing *st)
{
	r->pvsprites[r->num_pvsprites].thing_id = st->s;
	st->x = r->eng->things[st->s].x;
	st->y = r->eng->things[st->s].y;
	st->x -= r->eng->player.x;
	st->y -= r->eng->player.y;
	st->px = st->x * r->eng->cos_ang - st->y * r->eng->sin_ang;
	st->py = st->x * r->eng->sin_ang + st->y * r->eng->cos_ang;
	st->type = r->eng->things[st->s].type;
}

static inline void	append_to_viewspace(t_render *r, t_scansector *sc,
		t_scanthing *st)
{
	r->pvsprites[r->num_pvsprites].flags = 0;
	sc->info.flags = &r->pvsprites[r->num_pvsprites].flags;
	sc->info.col0 = &r->pvsprites[r->num_pvsprites].col0;
	sc->info.col1 = &r->pvsprites[r->num_pvsprites].col1;
	sc->info.dist0 = &r->pvsprites[r->num_pvsprites].dist0;
	sc->info.dist1 = &r->pvsprites[r->num_pvsprites].dist1;
	sc->info.playerspace = &r->pvsprites[r->num_pvsprites].playerspace;
	sc->info.screenspace = &r->pvsprites[r->num_pvsprites].screenspace;
	r->pvsprites[r->num_pvsprites].p.x = st->px;
	r->pvsprites[r->num_pvsprites].p.y = st->py;
	if (viewspace_clip_transform(&sc->l[ROTATED], &sc->info) == 1)
		r->num_pvsprites++;
}

void				scansector_things(t_render *r, t_scansector *sc)
{
	t_scanthing st;

	st.s = -1;
	while (++(st.s) < r->eng->num_things + r->eng->num_projectiles)
	{
		if (r->eng->things[st.s].sector == sc->scansects[sc->scansect_idx])
		{
			scansector_things2(r, &st);
			if (st.type == TH_MONSTER || st.type == TH_DEADMONSTER ||
					st.type == TH_IMPACT || st.type == TH_FIREBALL)
			{
				st.thing_ang = atan2(-st.py, -st.px);
				if (st.thing_ang > 0.0f)
					continue ;
			}
			else
				st.thing_ang = r->eng->things[st.s].attr.yaw + sc->angle;
			scansector_things3(r, sc, &st);
			if (!(sc->l[ROTATED].y0 < 0.0f && sc->l[ROTATED].y1 < 0.0f))
				append_to_viewspace(r, sc, &st);
		}
	}
}
