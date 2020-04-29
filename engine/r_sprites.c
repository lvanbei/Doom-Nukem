/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_sprites.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void		draw_sprites(t_render *r)
{
	t_draw_sprites ds;

	ds.i = -1;
	while (++ds.i < r->num_pvsprites)
		ds.draw_order[ds.i] = ds.i;
	ds.swapped = 1;
	while (ds.swapped)
	{
		ds.swapped = 0;
		ds.i = 0;
		while (++ds.i < r->num_pvsprites)
		{
			if (r->pvsprites[ds.draw_order[ds.i - 1]].p.y <
					r->pvsprites[ds.draw_order[ds.i]].p.y)
			{
				ds.tmp = ds.draw_order[ds.i - 1];
				ds.draw_order[ds.i - 1] = ds.draw_order[ds.i];
				ds.draw_order[ds.i] = ds.tmp;
				ds.swapped = 1;
			}
		}
	}
	ds.i = -1;
	while (++ds.i < r->num_pvsprites)
		draw_sprite(r, ds.draw_order[ds.i]);
}
