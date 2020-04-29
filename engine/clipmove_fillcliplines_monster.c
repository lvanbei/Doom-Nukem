/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipmove_fillcliplines_monster.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:40 by hde-moff          #+#    #+#             */
/*   Updated: 2019/11/25 15:52:05 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int					line_is_out_of_cb(t_clipmove_struct *cm, t_line2f l)
{
	if (((l.x0 < cm->cb.xmin) && (l.x1 < cm->cb.xmin))
			|| ((l.x0 > cm->cb.xmax) && (l.x1 > cm->cb.xmax))
			|| ((l.y0 < cm->cb.ymin) && (l.y1 < cm->cb.ymin))
			|| ((l.y0 > cm->cb.ymax) && (l.y1 > cm->cb.ymax)))
		return (1);
	return (0);
}

static inline void	init_monster(t_engine *eng, t_fillcliplines *fc, int i)
{
	fc->monster = eng->things[i];
	fc->x = fc->monster.x;
	fc->y = fc->monster.y;
	fc->px = eng->player.x - fc->x;
	fc->py = eng->player.y - fc->y;
	fc->thing_ang = atan2(fc->py, fc->px);
	fc->xv = cos(fc->thing_ang + M_PI / 2) *
		(eng->thing_width[TH_MONSTER] / 2.0f);
	fc->yv = sin(fc->thing_ang + M_PI / 2) *
		(eng->thing_width[TH_MONSTER] / 2.0f);
	fc->thing_l = (t_line2f) {fc->x - fc->xv, fc->y - fc->yv,
		fc->x + fc->xv, fc->y + fc->yv};
}

static inline void	init_monster2(t_fillcliplines *fc, t_thing *thing,
		t_clipmove_struct *cm)
{
	fc->thing_ztop = fc->monster.z;
	fc->thing_zlow = fc->monster.z - MONSTER_HEIGHT;
	fc->z = thing->z;
	fc->nz = fc->z + cm->cb.zv;
}

static inline void	init_monster3(t_fillcliplines *fc, t_clipmove_struct *cm,
		int i)
{
	cm->cl.lines[fc->clipline_idx] = fc->thing_l;
	cm->cl.line_thing_id[fc->clipline_idx++] = i;
	cm->cl.num_lines++;
}

void				fill_monsters(t_engine *eng, t_thing *thing,
		t_clipmove_struct *cm, t_fillcliplines *fc)
{
	int i;

	i = 0;
	while (i < eng->num_things)
	{
		if (eng->things[i].sector == cm->cl.clipsects[fc->clipsect_idx]
				&& eng->things[i].type == TH_MONSTER)
		{
			init_monster(eng, fc, i);
			if (line_is_out_of_cb(cm, fc->thing_l))
			{
				i++;
				continue ;
			}
			init_monster2(fc, thing, cm);
			if ((fc->z < fc->thing_zlow && fc->nz < fc->thing_zlow)
					|| (fc->z > fc->thing_ztop && fc->nz > fc->thing_ztop))
			{
				i++;
				continue ;
			}
			init_monster3(fc, cm, i);
		}
		i++;
	}
}
