/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipmove_fillcliplines.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:40 by hde-moff          #+#    #+#             */
/*   Updated: 2019/11/25 15:52:05 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void				fill_cliplines(t_engine *eng, t_thing *thing, int sectnum,
		t_clipmove_struct *cm)
{
	t_fillcliplines	fc;
	int				i;

	i = 0;
	while (i < MAX_CLIPLINES)
		cm->cl.line_thing_id[i++] = -1;
	fc.clipline_idx = 0;
	fc.clipsect_idx = 0;
	fc.sectnum = sectnum;
	cm->cl.clipsects[0] = sectnum;
	cm->cl.num_clipsects = 1;
	cm->cl.num_lines = 0;
	while (fc.clipsect_idx < cm->cl.num_clipsects)
	{
		if (cm->flags & CLIPMOVE_F_PROJ)
			fill_monsters(eng, thing, cm, &fc);
		fc.start_wall =
			eng->sectors[cm->cl.clipsects[fc.clipsect_idx]].start_wall;
		fc.end_wall = fc.start_wall +
			eng->sectors[cm->cl.clipsects[fc.clipsect_idx]].num_walls;
		fill_walls(eng, thing, cm, &fc);
		fc.clipsect_idx++;
	}
}
