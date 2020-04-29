/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_hud.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:21:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/25 09:58:49 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	draw_hud(const t_render *r)
{
	int y;

	y = 1;
	if (r->eng->r_flags & RF_DEBUG_HUD)
	{
		print_to_screen(r->eng->surface, (t_text) {&r->eng->font_table, 1, y,
				WHITE}, "bunches: %d", r->num_bunches);
		print_to_screen(r->eng->surface, (t_text) {&r->eng->font_table, 1,
				y += 9, WHITE}, "pvwalls: %d pv_sprites: %d",
				r->num_pvwalls, r->num_pvsprites);
		print_to_screen(r->eng->surface, (t_text) {&r->eng->font_table, 1,
				y += 9, WHITE}, "x: %f, y: %f, z:%f",
				r->eng->player.x, r->eng->player.y, r->eng->player.z);
		print_to_screen(r->eng->surface, (t_text) {&r->eng->font_table, 1,
				y += 9, WHITE}, "yaw: %f, pitch_shift: %d",
				r->eng->player.attr.yaw, r->eng->player_pitch_shift);
		y += 10;
	}
}
