/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jet_pack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:29 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:31 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void				update_percent_jp(t_player_items *p_i, int delta)
{
	static int		led = 1;

	if (p_i->jet_pack_led == 1 && p_i->inv_items[UI_ITEM_JET_PACK] == 1)
	{
		if (led)
		{
			led = 0;
			p_i->percent_jp--;
		}
		p_i->percent_jp -= (double)delta * 0.003f;
		if (p_i->percent_jp <= 0.0f)
		{
			p_i->percent_jp = 0;
			p_i->inv_items[UI_ITEM_JET_PACK] = 0;
			p_i->jet_pack_led = 0;
		}
	}
	else
		led = 1;
}

void				update_jetpack(t_engine *eng, t_player_items *p_i)
{
	if (p_i->inv_items[UI_ITEM_JET_PACK] == 1 && p_i->percent_jp > 0.0)
	{
		blit_number(eng, p_i->percent_jp, 8, 10);
		SDL_BlitSurface(p_i->ui_surface[UI_PERCENT], NULL,
		eng->surface, &p_i->ui_rect[11]);
		SDL_BlitSurface(p_i->ui_surface[UI_JET_PACK], NULL,
		eng->surface, &p_i->ui_rect[UI_RECT_JET_PACK]);
		if (!p_i->jet_pack_led)
			SDL_BlitSurface(p_i->ui_surface[UI_OFF_JP_LED], NULL,
			eng->surface, &p_i->ui_rect[UI_RECT_OFF_JP_LED]);
		else
			SDL_BlitSurface(p_i->ui_surface[UI_ON_JP_LED], NULL,
			eng->surface, &p_i->ui_rect[UI_RECT_ON_JP_LED]);
	}
}
