/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:40 by hde-moff          #+#    #+#             */
/*   Updated: 2019/11/25 15:52:05 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

double		f_clamp(double min, double a, double max)
{
	if (a < min)
		return (min);
	if (a > max)
		return (max);
	return (a);
}

int			i_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int			i_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

double		line_len(double x0, double y0, double x1, double y1)
{
	double	delta_x;
	double	delta_y;

	delta_x = x1 - x0;
	delta_y = y1 - y0;
	return (sqrt(fabs(delta_x * delta_x) + fabs(delta_y * delta_y)));
}

double		l_line_len(const t_line2f *l)
{
	double	delta_x;
	double	delta_y;

	delta_x = l->x1 - l->x0;
	delta_y = l->y1 - l->y0;
	return (sqrt(fabs(delta_x * delta_x) + fabs(delta_y * delta_y)));
}
