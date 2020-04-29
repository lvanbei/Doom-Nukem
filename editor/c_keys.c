/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static inline void		escape_seq(t_ed *ed)
{
	if (ed->tl_w.num_walls > 0)
		ed->tl_w.num_walls--;
	if (ed->istates.active_wall != -1)
		ed->istates.active_wall = -1;
	if (ed->istates.active_sector != -1)
		ed->istates.active_sector = -1;
	if (ed->istates.active_thing != -1)
		ed->istates.active_thing = -1;
}

void					handle_key(t_ed *ed, SDL_KeyboardEvent *e)
{
	if (e->keysym.scancode == SDL_SCANCODE_LEFT)
		ed->view.xmin += ed->view.dx_1 * -ARROWK_DELTA;
	if (e->keysym.scancode == SDL_SCANCODE_RIGHT)
		ed->view.xmin += ed->view.dx_1 * ARROWK_DELTA;
	if (e->keysym.scancode == SDL_SCANCODE_UP)
		ed->view.ymin += ed->view.dx_1 * ARROWK_DELTA;
	if (e->keysym.scancode == SDL_SCANCODE_DOWN)
		ed->view.ymin -= ed->view.dx_1 * ARROWK_DELTA;
	if (e->keysym.scancode == SDL_SCANCODE_SPACE)
		ed->istates.space_nav = (e->type == SDL_KEYDOWN);
	if (e->keysym.scancode == SDL_SCANCODE_S && !e->repeat)
		save_file(ed);
	if (e->keysym.sym == SDLK_LSHIFT)
		ed->istates.shift_down = (e->type == SDL_KEYDOWN) ? 1 : 0;
	if (e->type == SDL_KEYDOWN && e->keysym.sym == SDLK_ESCAPE && !e->repeat)
		escape_seq(ed);
	if (e->type == SDL_KEYDOWN && e->keysym.sym == SDLK_BACKSPACE
			&& !e->repeat)
	{
		if (ed->istates.active_sector != -1)
			delete_active_sector(ed);
		if (ed->istates.active_thing != -1)
			delete_active_thing(ed);
	}
}
