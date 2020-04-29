/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void		scansectors(t_render *r, int num_sector)
{
	t_scansector sc;

	sc.angle = M_PI / 2 - r->eng->player.attr.yaw;
	sc.scansect_idx = 0;
	sc.num_scansects = 1;
	r->num_bunches = -1;
	sc.new_bunch = 1;
	sc.scansects[0] = num_sector;
	while (sc.scansect_idx < sc.num_scansects)
	{
		sc.new_bunch = 1;
		scansector_things(r, &sc);
		scansector_walls(r, &sc);
		sc.scansect_idx++;
	}
	r->num_bunches += 1;
}

void			render(t_engine *eng)
{
	static t_render r = { .prev_yaw = -M_PI};

	r.eng = eng;
	r.num_pvwalls = 0;
	r.num_pvsprites = 0;
	eng->monster_in_front = -1;
	eng->wall_in_front = -1;
	scansectors(&r, eng->player.sector);
	draw_scene(&r);
	draw_sprites(&r);
	draw_hud(&r);
}
