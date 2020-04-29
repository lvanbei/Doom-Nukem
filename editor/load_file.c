/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 10:37:11 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/13 10:33:38 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int		read_walls(int fd, int *num_walls, t_wall *walls, int max_walls)
{
	if (read(fd, num_walls, sizeof(int)) != sizeof(int))
		return (0);
	if (*num_walls <= 0)
		return (0);
	else if (*num_walls >= max_walls)
		return (0);
	if (read(fd, walls, sizeof(t_wall) * *num_walls) !=
			(ssize_t)(sizeof(t_wall) * *num_walls))
		return (0);
	return (1);
}

static int		read_sectors(int fd, int *num_sectors, t_sector *sectors,
		int max_sectors)
{
	if (read(fd, num_sectors, sizeof(int)) != sizeof(int))
		return (0);
	if (*num_sectors >= max_sectors)
		return (0);
	if (*num_sectors <= 0)
		return (0);
	if (read(fd, sectors, sizeof(t_sector) * *num_sectors) !=
			(ssize_t)(sizeof(t_sector) * *num_sectors))
		return (0);
	return (1);
}

static int		read_things(int fd, int *num_things, t_thing *things,
		int max_things)
{
	if (read(fd, num_things, sizeof(int)) != sizeof(int))
		return (0);
	if (*num_things >= max_things)
		return (0);
	if (*num_things == 0)
		return (0);
	if (*num_things < 0)
		return (0);
	if (read(fd, things, sizeof(t_thing) * *num_things) !=
			(ssize_t)(sizeof(t_thing) * *num_things))
		return (0);
	return (1);
}

void			load_file(t_ed *ed)
{
	int fd;

	fd = open(ed->filename, O_RDONLY);
	if (fd < 0)
		abort_error(ed, "Couldn't open file: %s\n", ed->filename);
	if (!verify_code(fd))
		abort_error(ed, "wrong magic code!\n");
	if (!read_walls(fd, &ed->num_walls, ed->walls, MAX_WALLS))
		abort_error(ed, "couldn't read walls\n");
	if (!read_sectors(fd, &ed->num_sectors, ed->sectors, MAX_SECTORS))
		abort_error(ed, "couldn't read sectors\n");
	if (!read_player(fd, &ed->player))
		abort_error(ed, "couldn't read player\n");
	ed->player_set = 1;
	if (!read_things(fd, &ed->num_things, ed->things, MAX_THINGS))
		abort_error(ed, "couldn't read things\n");
	ft_printf("loaded map: %s\n", ed->filename);
	close(fd);
}
