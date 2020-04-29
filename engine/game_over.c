/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:37 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:34 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void			game_over_2(t_engine *eng, t_player_items *p_i,
	double timer)
{
	if (timer >= 700)
		SDL_BlitScaled(p_i->ui_surface[UI_LETTER_O], 0, eng->surface,
		&p_i->ui_rect[UI_RECT_L_O]);
	if (timer >= 850)
		SDL_BlitScaled(p_i->ui_surface[UI_LETTER_V], 0, eng->surface,
		&p_i->ui_rect[UI_RECT_L_V]);
	if (timer >= 1000)
		SDL_BlitScaled(p_i->ui_surface[UI_LETTER_E], 0, eng->surface,
		&p_i->ui_rect[UI_RECT_L_E_BIS]);
	if (timer >= 1150)
		SDL_BlitScaled(p_i->ui_surface[UI_LETTER_R], 0, eng->surface,
		&p_i->ui_rect[UI_RECT_L_R]);
}

void				game_over(t_engine *eng, t_player_items *p_i, double delta)
{
	static double	timer = 0;

	if ((int)p_i->life <= 0)
	{
		timer += delta;
		if (timer >= 100)
			SDL_BlitScaled(p_i->ui_surface[UI_LETTER_G], 0, eng->surface,
			&p_i->ui_rect[UI_RECT_L_G]);
		if (timer >= 250)
			SDL_BlitScaled(p_i->ui_surface[UI_LETTER_A], 0, eng->surface,
			&p_i->ui_rect[UI_RECT_L_A]);
		if (timer >= 400)
			SDL_BlitScaled(p_i->ui_surface[UI_LETTER_M], 0, eng->surface,
			&p_i->ui_rect[UI_RECT_L_M]);
		if (timer >= 550)
			SDL_BlitScaled(p_i->ui_surface[UI_LETTER_E], 0, eng->surface,
			&p_i->ui_rect[UI_RECT_L_E]);
		game_over_2(eng, p_i, timer);
	}
}
