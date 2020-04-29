/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_display_number.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:17:12 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:23 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void			blit_number_2(t_engine *eng, int nbr, int index, int typo)
{
	int				tmp;

	tmp = 0;
	if (nbr >= 10 && nbr <= 99)
	{
		tmp = nbr / 10;
		if (tmp % 10 == 1 && typo != 10)
			SDL_BlitSurface(eng->p_i.ui_surface[tmp % 10 + typo], NULL,
			eng->surface, &eng->p_i.ui_rect[index + 3]);
		else
			SDL_BlitSurface(eng->p_i.ui_surface[tmp % 10 + typo], NULL,
			eng->surface, &eng->p_i.ui_rect[index + 1]);
		SDL_BlitSurface(eng->p_i.ui_surface[nbr % 10 + typo], NULL,
		eng->surface, &eng->p_i.ui_rect[index + 2]);
	}
	if (nbr <= 9)
	{
		SDL_BlitSurface(eng->p_i.ui_surface[0 + typo], NULL,
		eng->surface, &eng->p_i.ui_rect[index + 1]);
		SDL_BlitSurface(eng->p_i.ui_surface[nbr + typo], NULL,
		eng->surface, &eng->p_i.ui_rect[index + 2]);
	}
}

void				blit_number(t_engine *eng, int number, int index, int typo)
{
	t_player_items	*p_i;
	int				tmp;

	p_i = &eng->p_i;
	tmp = 0;
	if (number >= 100)
	{
		SDL_BlitSurface(p_i->ui_surface[1 + typo], NULL, eng->surface,
		&p_i->ui_rect[index + 0]);
		tmp = number / 10;
		if (tmp % 10 == 1 && typo != 10)
			SDL_BlitSurface(p_i->ui_surface[tmp % 10 + typo], NULL,
			eng->surface, &p_i->ui_rect[index + 3]);
		else
			SDL_BlitSurface(p_i->ui_surface[tmp % 10 + typo], NULL,
			eng->surface, &p_i->ui_rect[index + 1]);
		SDL_BlitSurface(p_i->ui_surface[number % 10 + typo], NULL,
		eng->surface, &p_i->ui_rect[index + 2]);
	}
	blit_number_2(eng, number, index, typo);
}
