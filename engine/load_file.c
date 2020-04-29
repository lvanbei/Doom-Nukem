/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:20:30 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/04 12:46:50 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int		read_allocwalls(int fd, int *num_walls, t_wall **walls)
{
	if (read(fd, num_walls, sizeof(int)) != sizeof(int))
		return (0);
	if (*num_walls <= 0)
		return (0);
	else if (*num_walls >= MAX_WALLS)
		return (0);
	*walls = (t_wall *)malloc(sizeof(t_wall) * *num_walls);
	if (*walls == NULL)
		return (0);
	if (read(fd, *walls, sizeof(t_wall) * *num_walls) !=
			(ssize_t)(sizeof(t_wall) * *num_walls))
		return (0);
	return (1);
}

static int		read_allocsectors(int fd, int *num_sectors, t_sector **sectors)
{
	if (read(fd, num_sectors, sizeof(int)) != sizeof(int))
		return (0);
	if (*num_sectors <= 0)
		return (0);
	else if (*num_sectors >= MAX_SECTORS)
		return (0);
	*sectors = (t_sector *)malloc(sizeof(t_sector) * *num_sectors);
	if (*sectors == NULL)
		return (0);
	if (read(fd, *sectors, sizeof(t_sector) * *num_sectors) !=
			(ssize_t)(sizeof(t_sector) * *num_sectors))
		return (0);
	return (1);
}

static int		read_allocthings(int fd, int *num_things, t_thing **things)
{
	if (read(fd, num_things, sizeof(int)) != sizeof(int))
		return (0);
	if (*num_things < 0)
		return (0);
	else if (*num_things >= MAX_THINGS)
		return (0);
	*things = (t_thing *)malloc(sizeof(t_thing) * (*num_things +
				MAX_NUM_PROJECTILES));
	if (*things == NULL)
		return (0);
	if (read(fd, *things, sizeof(t_thing) * *num_things) !=
			(ssize_t)(sizeof(t_thing) * *num_things))
		return (0);
	return (1);
}

void			load_file2(t_engine *eng, int fd)
{
	if (!read_alloctextures(fd, &eng->num_textures, &eng->textures))
		abort_error(eng, "failed read_alloctextures\n");
	if (!read_alloctextures(fd, &eng->num_thing_textures,
				&eng->thing_textures))
		abort_error(eng, "failed read_alloctextures things\n");
	if (!read_alloctextures(fd, NULL, &eng->menu.surfaces))
		abort_error(eng, "failed read_alloctextures menu surfaces\n");
	if (!read_alloctextures(fd, NULL, &eng->p_i.ui_surface))
		abort_error(eng, "faled read_alloctextures ui surfaces\n");
	if (!read_allocsounds(fd, NULL, &eng->p_i.ui_sound))
		abort_error(eng, "failed read_allocsounds\n");
}

void			load_file(t_engine *eng, char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		abort_error(eng, "Couldn't open file: %s\n", str);
	if (!verify_code(fd))
		abort_error(eng, "couldn't recognize magic code\n");
	if (!read_allocwalls(fd, &eng->num_walls, &eng->walls))
		abort_error(eng, "failed: read_allocwalls\n");
	if (!read_allocsectors(fd, &eng->num_sectors, &eng->sectors))
		abort_error(eng, "failed: read_allocsectors\n");
	if (!read_player(fd, &eng->player))
		abort_error(eng, "failed: read_player\n");
	if (!read_allocthings(fd, &eng->num_things, &eng->things))
		abort_error(eng, "failed read_allocthings\n");
	if (eng->num_things >= MAX_PVSPRITES)
		ft_printf("WARNING: more things than pvsprites available\n");
	load_file2(eng, fd);
	close(fd);
	ft_printf("loaded map: %s\n", str);
}
