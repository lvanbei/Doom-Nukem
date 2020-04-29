/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			screen_to_map(t_view *view, t_v2 p, double *dest_x,
		double *dest_y)
{
	*dest_x = view->xmin + (p.x * view->dx_1);
	*dest_y = (-(p.y - (GRID_HEIGHT + 1)) * view->dx_1) + view->ymin;
}

void			handle_scroll(t_ed *ed, SDL_MouseWheelEvent *e)
{
	double	delta;
	double	tmp;

	delta = (e->y * ed->view.w / 20);
	tmp = ed->view.w + delta;
	if (tmp > MIN_WIDTH && tmp < MAX_WIDTH)
	{
		ed->view.w = tmp;
		delta /= 2.0f;
		ed->view.xmin -= delta;
		ed->view.ymin -= delta;
		ed->view.dx = GRID_WIDTH / ed->view.w;
		ed->view.dx_1 = ed->view.w / (double)GRID_WIDTH;
	}
}

int				point_in_rect(int x, int y, const SDL_Rect *rect)
{
	if (x >= rect->x && y >= rect->y
			&& x <= (rect->x + rect->w) && y <= (rect->y + rect->h))
		return (1);
	return (0);
}

int				was_pressed(t_istates *istates, SDL_Event *e, enum e_mb mb)
{
	if (mb == LMB)
	{
		if (istates->mb_down[mb] == 0 && e->type == SDL_MOUSEBUTTONDOWN &&
				e->button.button == SDL_BUTTON_LEFT)
		{
			istates->mb_down[mb] = 1;
			return (1);
		}
	}
	else if (mb == RMB)
	{
		if (istates->mb_down[mb] == 0 && e->type == SDL_MOUSEBUTTONDOWN &&
				e->button.button == SDL_BUTTON_RIGHT)
		{
			istates->mb_down[mb] = 1;
			return (1);
		}
	}
	return (0);
}

int				was_released(t_istates *istates, SDL_Event *e, enum e_mb mb)
{
	if (mb == LMB)
	{
		if (istates->mb_down[mb] == 1 && e->type == SDL_MOUSEBUTTONUP &&
				e->button.button == SDL_BUTTON_LEFT)
		{
			istates->mb_down[mb] = 0;
			return (1);
		}
	}
	else if (mb == RMB)
	{
		if (istates->mb_down[mb] == 1 && e->type == SDL_MOUSEBUTTONUP &&
				e->button.button == SDL_BUTTON_RIGHT)
		{
			istates->mb_down[mb] = 0;
			return (1);
		}
	}
	return (0);
}
