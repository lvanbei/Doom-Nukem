/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_scansector_viewspace.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline int		viewspace_sub0(const t_line2f *l, t_clip *info,
		t_viewspace *v)
{
	if ((l->x0 > l->y0) || l->y0 == 0)
		return (0);
	v->col0 = WIN_WIDTH / 2 + ((l->x0 * WIN_WIDTH / 2) / l->y0);
	if (v->col0 >= WIN_WIDTH)
	{
		v->col0 = WIN_WIDTH - 1;
		*(info->flags) |= PV_CLIPPED0;
		v->screenspace.x0 = v->screenspace.y0;
	}
	v->dist0 = l->y0;
	return (1);
}

static inline int		viewspace_sub1(const t_line2f *l, t_clip *info,
		t_viewspace *v)
{
	if (l->x1 < -l->y1)
		return (0);
	v->col0 = 0;
	v->dist0 = intersectyminx(l);
	*(info->flags) |= PV_CLIPPED0;
	v->screenspace.y0 = v->dist0;
	v->screenspace.x0 = -v->dist0;
	return (1);
}

static inline int		viewspace_sub3(const t_line2f *l, t_clip *info,
		t_viewspace *v)
{
	if (l->x0 > l->y0)
		return (0);
	v->col1 = WIN_WIDTH - 1;
	v->dist1 = intersectyx(l);
	*(info->flags) |= PV_CLIPPED1;
	v->screenspace.x1 = v->dist1;
	v->screenspace.y1 = v->dist1;
	return (1);
}

static inline int		viewspace_sub2(const t_line2f *l, t_clip *info,
		t_viewspace *v)
{
	if (l->x1 <= l->y1)
	{
		if ((l->x1 < -l->y1) || l->y1 == 0)
			return (0);
		v->col1 = WIN_WIDTH / 2 + ((l->x1 * WIN_WIDTH / 2) / l->y1) - 1;
		if (v->col1 >= WIN_WIDTH)
		{
			v->col1 = WIN_WIDTH - 1;
			*(info->flags) |= PV_CLIPPED1;
			v->screenspace.x1 = v->screenspace.y1;
		}
		v->dist1 = l->y1;
	}
	else
	{
		if (!viewspace_sub3(l, info, v))
			return (0);
	}
	return (1);
}

int						viewspace_clip_transform(const t_line2f *l,
		t_clip *info)
{
	t_viewspace v;

	v.screenspace = *l;
	*(info->playerspace) = *l;
	if (l->x0 >= -l->y0)
	{
		if (!viewspace_sub0(l, info, &v))
			return (0);
	}
	else
	{
		if (!viewspace_sub1(l, info, &v))
			return (0);
	}
	if (v.dist0 <= 0)
		return (0);
	if (!viewspace_sub2(l, info, &v))
		return (0);
	if (v.dist1 <= 0.0f || v.col0 >= v.col1)
		return (0);
	return (viewspace_sub4(info, &v));
}
