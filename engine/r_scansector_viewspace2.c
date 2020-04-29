/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_scansector_viewspace2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

double	intersectyminx(const t_line2f *l)
{
	double m;

	if (l->x1 == l->x0)
		return (-l->x0);
	m = (l->y1 - l->y0) / (l->x1 - l->x0);
	return (((-m * l->x0) + l->y0) / (m + 1));
}

double	intersectyx(const t_line2f *l)
{
	double m;

	if (l->x1 == l->x0)
		return (l->x0);
	m = (l->y1 - l->y0) / (l->x1 - l->x0);
	return (((-m * l->x0) + l->y0) / (1 - m));
}

int		viewspace_sub4(t_clip *info,
		t_viewspace *v)
{
	*(info->col0) = v->col0;
	*(info->dist0) = v->dist0;
	*(info->col1) = v->col1;
	*(info->dist1) = v->dist1;
	*(info->screenspace) = v->screenspace;
	return (1);
}
