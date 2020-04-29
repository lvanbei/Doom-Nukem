/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_select_sector2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	delete_active_sector(void *a)
{
	t_ed *ed;

	ed = (t_ed *)a;
	delete_sector(ed, ed->istates.active_sector);
	ed->istates.active_sector = -1;
	ed->istates.hot_sector = -1;
}

void	tl_select_sector(t_ed *ed, int screen_x, int screen_y, int down)
{
	int		hit_sector;
	double	p_x;
	double	p_y;

	screen_to_map(&ed->view, (t_v2) {screen_x, screen_y}, &p_x, &p_y);
	hit_sector = get_parent_sector(ed, p_x, p_y);
	ed->istates.hot_sector = hit_sector;
	if (down)
	{
		ed->istates.active_sector = hit_sector;
		if (hit_sector >= 0)
		{
			ed->context_menu[TL_SELECT_SECTOR].tex_pick_p[TXP_FLOOR] =
				&ed->sectors[hit_sector].floor_texture;
			ed->context_menu[TL_SELECT_SECTOR].tex_pick_p[TXP_CEIL] =
				&ed->sectors[hit_sector].ceiling_texture;
			ed->context_menu[TL_SELECT_SECTOR].var_control[0] =
				&ed->sectors[hit_sector].floor_height;
			ed->context_menu[TL_SELECT_SECTOR].var_control[1] =
				&ed->sectors[hit_sector].ceiling_height;
		}
	}
}
