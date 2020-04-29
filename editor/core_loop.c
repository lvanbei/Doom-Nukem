/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core-loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		init_main(t_ed *ed)
{
	init_ed0(ed);
	init_ed1(ed);
	init_ed2(ed);
	init_ed3(ed);
	init_ed4(ed);
	init_ed5(ed);
	init_ed6(ed);
	init_ed7(ed);
	init_ed8(ed);
}

void			core_loop(t_ed *ed)
{
	SDL_Event e;

	init_main(ed);
	while (1)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT ||
					(e.type == SDL_KEYDOWN && e.key.keysym.scancode ==
					SDL_SCANCODE_Q))
				return ;
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
				handle_key(ed, &e.key);
			if (e.type == SDL_MOUSEWHEEL)
				handle_scroll(ed, &e.wheel);
			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN ||
					e.type == SDL_MOUSEBUTTONUP)
				handle_mouse(ed, &e);
		}
		render(ed);
	}
}
