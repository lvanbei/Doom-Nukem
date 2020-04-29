/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_grid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		v_line(SDL_Surface *surface, int x, int color)
{
	uint32_t	*dest;
	int			count;

	dest = &(((uint32_t *)surface->pixels)[x]);
	count = GRID_HEIGHT;
	while (count--)
	{
		*dest = color;
		dest += WIN_WIDTH;
	}
}

static void		h_line(SDL_Surface *surface, int y, int color)
{
	uint32_t	*dest;
	int			count;

	dest = &(((uint32_t *)surface->pixels)[WIN_WIDTH * y]);
	count = GRID_WIDTH;
	while (count--)
	{
		*dest = color;
		dest += 1;
	}
}

void			map_to_screen(const t_view *view, t_v2f p, double *x, double *y)
{
	*x = (p.x - view->xmin) * view->dx;
	*y = (p.y - view->ymin) * view->dx;
	*y = (GRID_HEIGHT - 1) - *y;
}

void			draw_grid(SDL_Surface *surface, const t_view *view)
{
	double	x;
	double	y;

	map_to_screen(view, (t_v2f) {ceil(view->xmin), 0}, &x, &y);
	while (x < GRID_WIDTH)
	{
		v_line(surface, x, 0xFF383434);
		x += view->dx;
	}
	map_to_screen(view, (t_v2f) {0, ceil(view->ymin)}, &x, &y);
	while (y > 0)
	{
		h_line(surface, y, 0xFF383434);
		y -= view->dx;
	}
	v_line(surface, GRID_WIDTH - 2, 0xFF0000FF);
	v_line(surface, GRID_WIDTH - 1, 0xFF0000FF);
}
