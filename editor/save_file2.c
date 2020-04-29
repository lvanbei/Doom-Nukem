/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_file2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:07:38 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/25 10:09:26 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		write_code(int fd)
{
	if (write(fd, (void *)"FUCKYOU!", 8) != 8)
		return (0);
	return (1);
}

int		write_walls(int fd, uint32_t num_walls,
		const t_wall walls[MAX_WALLS])
{
	if (write(fd, (void *)&num_walls, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (write(fd, (void *)walls, sizeof(t_wall) * num_walls) !=
			(ssize_t)(sizeof(t_wall) * num_walls))
		return (0);
	return (1);
}

int		write_sectors(int fd, uint32_t num_sectors,
		const t_sector sectors[MAX_SECTORS])
{
	if (write(fd, (void *)&num_sectors, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (write(fd, (void *)sectors, sizeof(t_sector) * num_sectors) !=
			(ssize_t)(sizeof(t_sector) * num_sectors))
		return (0);
	return (1);
}

int		write_player(int fd, const t_thing *player)
{
	if (write(fd, (void *)player, sizeof(t_thing)) != sizeof(t_thing))
		return (0);
	return (1);
}

int		write_things(int fd, uint32_t num_things,
		const t_thing things[MAX_THINGS])
{
	if (write(fd, (void *)&num_things, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (write(fd, (void *)things, sizeof(t_thing) * num_things) !=
			(ssize_t)(sizeof(t_thing) * num_things))
		return (0);
	return (1);
}
