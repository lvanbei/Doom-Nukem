/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_guard2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:07:38 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/25 10:09:26 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static inline int	safety_checks2(t_ed *ed)
{
	if (ed->num_walls < 3)
	{
		ft_printf("to make polygons with less than 3 walls\n");
		return (0);
	}
	if (ed->num_sectors == 0)
	{
		ft_printf("no sectors\n");
		return (0);
	}
	if (!ed->player_set)
	{
		ft_printf("no player set!\n");
		return (0);
	}
	if (!inside_sector(ed, ed->player.x, ed->player.y, ed->player.sector))
	{
		ft_printf("player not in sector");
		return (0);
	}
	return (1);
}

static inline int	check_sectors_height(t_ed *ed)
{
	int i;

	i = -1;
	while (++i < ed->num_sectors)
	{
		if (ed->sectors[i].floor_height > ed->sectors[i].ceiling_height - 2)
		{
			ft_printf("sector[%d] with floor: %f and ceil: %f does not"
					"meet minimum height requirements\n", i,
					ed->sectors[i].floor_height, ed->sectors[i].ceiling_height);
			return (0);
		}
	}
	return (1);
}

static inline int	map_has_ending(t_ed *ed)
{
	int				i;
	unsigned char	ending_set;

	ending_set = 0;
	i = -1;
	while (++i < ed->num_things)
	{
		if (!inside_sector(ed, ed->things[i].x, ed->things[i].y,
					ed->things[i].sector))
		{
			ft_printf("thing[%d] not in sector\n", i);
			return (0);
		}
		if (!ending_set)
		{
			if (ed->things[i].type == TH_MOUSE_ENDING)
				ending_set = 1;
		}
	}
	if (!ending_set)
	{
		ft_printf("no ending set!\n");
		return (0);
	}
	return (1);
}

int					safety_checks(t_ed *ed)
{
	if (!safety_checks2(ed))
		return (0);
	if (!check_sectors_height(ed))
		return (0);
	if (!map_has_ending(ed))
		return (0);
	return (1);
}
