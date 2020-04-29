/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_pause.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:32 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:33 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	display_menu(t_engine *eng, t_player_items *p_i, int pause_game)
{
	if (pause_game && (int)p_i->life > 0 && !eng->p_i.win)
		SDL_BlitSurface(p_i->ui_surface[UI_KEYS_MENU], 0, eng->surface, 0);
}
