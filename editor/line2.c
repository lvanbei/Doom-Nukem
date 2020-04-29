/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line2,c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void					draw_pixel(SDL_Surface *screen, int x, int y, int color)
{
	((uint32_t *)screen->pixels)[x + WIN_WIDTH * y] = color;
}

void					draw_line5(SDL_Surface *screen, t_line2 *l, t_drawl *d,
int color)
{
	d->error_adj = (double)d->delta_y / (double)d->delta_x;
	while (--d->delta_x)
	{
		d->error_acctmp = (int)d->error_acc;
		d->error_acc += d->error_adj;
		if ((int)d->error_acc > d->error_acctmp)
			l->y0++;
		l->x0 += d->xdir;
		draw_pixel(screen, l->x0, l->y0, color);
	}
}
