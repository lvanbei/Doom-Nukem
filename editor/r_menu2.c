/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_menu2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		draw_menu_tool(t_ed *ed)
{
	int	colors[TL_END];
	int	i;

	slow_memset(colors, 0xFF, TL_END * sizeof(int));
	if (ed->istates.hot_tool != TL_NONE)
		colors[ed->istates.hot_tool] = GREEN;
	colors[ed->istates.active_tool] = YELLOW;
	i = -1;
	while (++i < TL_END)
		print_to_screen(ed->surface, (t_text) {&ed->font_table,
				ed->tool_textbounds[i].x, ed->tool_textbounds[i].y,
				colors[i]}, "%s", ed->tool_name[i]);
}

void		draw_rect2(SDL_Surface *surface, int color, t_draw_rect *dr)
{
	dr->dest = &(((uint32_t *)surface->pixels)[dr->x0 + WIN_WIDTH * dr->y0]);
	dr->len = dr->y1 - dr->y0;
	while (dr->len--)
	{
		*(dr->dest) = color;
		dr->dest += WIN_WIDTH;
	}
	dr->dest = &(((uint32_t *)surface->pixels)[dr->x1 + WIN_WIDTH * dr->y0]);
	dr->len = dr->y1 - dr->y0;
	while (dr->len--)
	{
		*(dr->dest) = color;
		dr->dest += WIN_WIDTH;
	}
}

void		draw_rect(SDL_Surface *surface, const SDL_Rect *rect, int color)
{
	t_draw_rect dr;

	dr.x0 = rect->x;
	dr.x1 = dr.x0 + rect->w;
	dr.y0 = rect->y;
	dr.y1 = dr.y0 + rect->h;
	dr.dest = &(((uint32_t *)surface->pixels)[dr.x0 + WIN_WIDTH * dr.y0]);
	dr.len = dr.x1 - dr.x0;
	while (dr.len--)
	{
		*(dr.dest) = color;
		dr.dest++;
	}
	dr.dest = &(((uint32_t *)surface->pixels)[dr.x0 + WIN_WIDTH * dr.y1]);
	dr.len = dr.x1 - dr.x0;
	while (dr.len--)
	{
		*(dr.dest) = color;
		dr.dest++;
	}
	draw_rect2(surface, color, &dr);
}

void		draw_thing_types(t_ed *ed)
{
	int i;

	i = -1;
	while (++i < TH_VISIBLE_END)
	{
		SDL_BlitSurface(ed->ed_textures[i], NULL,
				ed->surface, &ed->thing_typebounds[i]);
	}
	if (ed->istates.th_hot != TH_NONE)
		draw_rect(ed->surface, &ed->thing_typebounds[ed->istates.th_hot],
				GREEN);
	draw_rect(ed->surface, &ed->thing_typebounds[ed->istates.th_active],
			YELLOW);
}
