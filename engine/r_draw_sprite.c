/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void			draw_col(SDL_Surface *screen, t_draw_col dc)
{
	uint32_t	*dest;
	uint32_t	color;
	int			count;

	count = dc.yh - dc.yl;
	if (count < 0)
		return ;
	dest = &(((uint32_t *)screen->pixels)[dc.x + WIN_WIDTH * dc.yl]);
	while (count--)
	{
		color = ((uint32_t *)dc.texture->pixels)[(dc.u % dc.texture->w) +
			dc.texture->w * ((int)(dc.v) % dc.texture->h)];
		if (color != 0x00FC00FC)
			*dest = color;
		dest += WIN_WIDTH;
		dc.v += dc.v_step;
	}
}

static inline void	ds_func0(t_render *r, t_draw_sprite *ds)
{
	ds->scale1 = R_WALL_HEIGHT / ds->pvsprite->dist1;
	ds->p_zh = (ds->thing.z) - r->eng->player.z;
	ds->p_zl = (ds->thing.z - r->eng->thing_height[ds->type]) -
		r->eng->player.z;
	ds->x0_yl = HEIGHT_CENTER - (ds->p_zh * ds->scale0) + r->eng->PPS;
	ds->x0_yh = HEIGHT_CENTER - (ds->p_zl * ds->scale0) + r->eng->PPS;
	ds->x1_yl = HEIGHT_CENTER - (ds->p_zh * ds->scale1) + r->eng->PPS;
	ds->x1_yh = HEIGHT_CENTER - (ds->p_zl * ds->scale1) + r->eng->PPS;
	ds->thing_screen_width = (ds->pvsprite->col1 - ds->pvsprite->col0) + 1;
	ds->yl_step = (ds->x1_yl - ds->x0_yl) / ds->thing_screen_width;
	ds->yh_step = (ds->x1_yh - ds->x0_yh) / ds->thing_screen_width;
	ds->yl_frac = ds->x0_yl + (ds->yl_step * (ds->x0 - ds->pvsprite->col0));
	ds->yh_frac = ds->x0_yh + (ds->yh_step * (ds->x0 - ds->pvsprite->col0));
	if (ds->thing.type == TH_MONSTER && ds->x0 <= WIDTH_CENTER && ds->x1 >=
			WIDTH_CENTER)
	{
		if (ds->umost[WIDTH_CENTER] < ds->dmost[WIDTH_CENTER])
		{
			ds->f_yl = ds->yl_frac + (ds->yl_step * (WIDTH_CENTER - ds->x0));
			ds->f_yh = ds->yh_frac + (ds->yh_step * (WIDTH_CENTER - ds->x0));
			if (ds->f_yl <= HEIGHT_CENTER && ds->f_yh >= HEIGHT_CENTER)
				r->eng->monster_in_front = ds->pvsprite->thing_id;
		}
	}
	ds->count = (ds->x0 - ds->pvsprite->col0);
}

static inline void	ds_func1(t_render *r, t_draw_sprite *ds)
{
	ds->texture = r->eng->thing_textures[ds->type];
	ds->seg = ds->pvsprite->playerspace;
	ds->sprite_len = line_len(ds->seg.x0, ds->seg.y0, ds->seg.x1, ds->seg.y1);
	ds->u0 = 0;
	ds->u1 = ds->texture->w;
	ds->u_range = ds->u1 - ds->u0;
	if (ds->pvsprite->flags & PV_CLIPPED0)
	{
		ds->wp_pl = line_len(ds->seg.x0, ds->seg.y0,
				ds->pvsprite->screenspace.x0,
				ds->pvsprite->screenspace.y0);
		ds->u0 = (ds->wp_pl / ds->sprite_len) * ds->u_range;
	}
	if (ds->pvsprite->flags & PV_CLIPPED1)
	{
		ds->wp_pl = line_len(ds->seg.x0, ds->seg.y0,
				ds->pvsprite->screenspace.x1,
				ds->pvsprite->screenspace.y1);
		ds->u1 = (ds->wp_pl / ds->sprite_len) * ds->u_range;
	}
	ds->u0_z0 = ds->u0 / ds->pvsprite->dist0;
	ds->u1_z1 = ds->u1 / ds->pvsprite->dist1;
	ds->f1_z0 = 1.0f / ds->pvsprite->dist0;
	ds->f1_z1 = 1.0f / ds->pvsprite->dist1;
	ds->scale0 = R_WALL_HEIGHT / ds->pvsprite->dist0;
}

static inline void	ds_loop(t_render *r, t_draw_sprite *ds, int i)
{
	ds->v = 0;
	ds->v_step = (ds->texture->h) / (ds->yh_frac - ds->yl_frac);
	ds->yl = ds->yl_frac;
	ds->yh = ds->yh_frac;
	if (ds->yl < ds->umost[i])
	{
		ds->v = (ds->umost[i] - ds->yl) * ds->v_step;
		ds->yl = ds->umost[i];
	}
	else if (ds->yl > ds->dmost[i])
		ds->yl = ds->dmost[i];
	if (ds->yh < ds->yl)
		ds->yh = ds->yl;
	else if (ds->yh > ds->dmost[i])
		ds->yh = ds->dmost[i];
	ds->alpha = ds->count / ds->thing_screen_width;
	ds->u = (((1 - ds->alpha) * ds->u0_z0) + (ds->alpha * ds->u1_z1)) /
		(((1 - ds->alpha) * ds->f1_z0) + (ds->alpha * ds->f1_z1));
	draw_col(r->eng->surface, (t_draw_col) {i, ds->yl, ds->yh, ds->texture,
			ds->u, ds->v, ds->v_step});
	ds->count += 1;
	ds->yl_frac += ds->yl_step;
	ds->yh_frac += ds->yh_step;
}

void				draw_sprite(t_render *r, int sprite_id)
{
	t_draw_sprite	ds;
	int				x;

	ds.pvsprite = &r->pvsprites[sprite_id];
	ds.thing = r->eng->things[ds.pvsprite->thing_id];
	if (ds.thing.type == TH_NONE)
		return ;
	slow_bzero(ds.umost, sizeof(ds.umost));
	x = -1;
	while (++x < WIN_WIDTH)
		ds.dmost[x] = WIN_HEIGHT - 1;
	ds.type = ds.thing.type;
	ds.x0 = ds.pvsprite->col0;
	ds.x1 = ds.pvsprite->col1;
	if (!clipsprite(r, sprite_id, &ds))
		return ;
	ds_func1(r, &ds);
	ds_func0(r, &ds);
	x = ds.x0 - 1;
	while (++x <= ds.x1)
		ds_loop(r, &ds, x);
}
