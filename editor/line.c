/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void				draw_line2(SDL_Surface *screen, t_line2 *l, t_drawl *d,
int color)
{
	if (l->y0 > l->y1)
	{
		d->tmp = l->y0;
		l->y0 = l->y1;
		l->y1 = d->tmp;
		d->tmp = l->x0;
		l->x0 = l->x1;
		l->x1 = d->tmp;
	}
	draw_pixel(screen, l->x0, l->y0, color);
	d->delta_x = l->x1 - l->x0;
	if (d->delta_x >= 0)
		d->xdir = 1;
	else
	{
		d->xdir = -1;
		d->delta_x = -d->delta_x;
	}
	d->delta_y = l->y1 - l->y0;
}

int					draw_line3(SDL_Surface *screen, t_line2 *l, t_drawl *d,
int color)
{
	if (d->delta_y == 0)
	{
		while (d->delta_x-- != 0)
		{
			l->x0 += d->xdir;
			draw_pixel(screen, l->x0, l->y0, color);
		}
		return (0);
	}
	if (d->delta_x == 0)
	{
		l->y0++;
		draw_pixel(screen, l->x0, l->y0, color);
		while (--d->delta_y != 0)
		{
			l->y0++;
			draw_pixel(screen, l->x0, l->y0, color);
		}
		return (0);
	}
	return (1);
}

int					draw_line4(SDL_Surface *screen, t_line2 *l, t_drawl *d,
int color)
{
	if (d->delta_y > d->delta_x)
	{
		d->error_adj = (double)d->delta_x / (double)d->delta_y;
		while (--d->delta_y)
		{
			d->error_acctmp = (int)d->error_acc;
			d->error_acc += d->error_adj;
			if ((int)d->error_acc > d->error_acctmp)
				l->x0 += d->xdir;
			l->y0++;
			draw_pixel(screen, l->x0, l->y0, color);
		}
		draw_pixel(screen, l->x1, l->y1, color);
		return (0);
	}
	return (1);
}

void				draw_line(SDL_Surface *screen, t_line2 l,
		int color)
{
	t_drawl	d;

	draw_line2(screen, &l, &d, color);
	if (!draw_line3(screen, &l, &d, color))
		return ;
	if (d.delta_y == d.delta_x)
	{
		l.x0 += d.xdir;
		l.y0++;
		draw_pixel(screen, l.x0, l.y0, color);
		while (--d.delta_y != 0)
		{
			l.x0 += d.xdir;
			l.y0++;
			draw_pixel(screen, l.x0, l.y0, color);
		}
		return ;
	}
	d.error_acc = 0.0f;
	if (!draw_line4(screen, &l, &d, color))
		return ;
	draw_line5(screen, &l, &d, color);
	draw_pixel(screen, l.x1, l.y1, color);
}
