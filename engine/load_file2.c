/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:20:30 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/04 12:46:50 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline int		read_alloctexture(int fd, SDL_Surface ***textures,
		t_rat rat)
{
	if (read(fd, &rat.w, sizeof(int)) != sizeof(int))
		return (0);
	if (read(fd, &rat.h, sizeof(int)) != sizeof(int))
		return (0);
	if (read(fd, &rat.pitch, sizeof(int)) != sizeof(int))
		return (0);
	if (read(fd, &rat.bpp, sizeof(uint8_t)) != sizeof(uint8_t))
		return (0);
	if (read(fd, &rat.rmask, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (read(fd, &rat.gmask, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (read(fd, &rat.bmask, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (read(fd, &rat.amask, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	rat.pixels = malloc(rat.pitch * rat.h);
	if (rat.pixels == NULL || (read(fd, rat.pixels, rat.pitch * rat.h) !=
				rat.pitch * rat.h))
		return (0);
	(*textures)[rat.i] = SDL_CreateRGBSurfaceFrom(rat.pixels, rat.w, rat.h,
			rat.bpp, rat.pitch, rat.rmask, rat.gmask, rat.bmask, rat.amask);
	if ((*textures)[rat.i] == NULL)
		return (0);
	return (1);
}

int						read_alloctextures(int fd, int *num_textures,
		SDL_Surface ***textures)
{
	t_rat	rat;

	rat.n_textures = 0;
	if (read(fd, &rat.n_textures, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (num_textures)
		*num_textures = rat.n_textures;
	if (rat.n_textures <= 0)
		return (0);
	*textures = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * rat.n_textures);
	if (*textures == NULL)
		return (0);
	rat.i = -1;
	while (++rat.i < rat.n_textures)
		(*textures)[rat.i] = NULL;
	rat.i = -1;
	while (++rat.i < rat.n_textures)
	{
		if (!read_alloctexture(fd, textures, rat))
			return (0);
	}
	return (1);
}

static inline int		read_allocsound(int fd, Mix_Chunk ***ui_sounds,
		t_ras r)
{
	if (read(fd, &r.alen, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	r.buf = malloc(r.alen);
	if (r.buf == NULL)
		return (0);
	if (read(fd, r.buf, r.alen) != r.alen)
		return (0);
	(*ui_sounds)[r.i] = Mix_QuickLoad_RAW(r.buf, r.alen);
	if ((*ui_sounds)[r.i] == NULL)
		return (0);
	return (1);
}

int						read_allocsounds(int fd, int *num_sounds,
		Mix_Chunk ***ui_sounds)
{
	t_ras r;

	r.n_sounds = 0;
	if (read(fd, &r.n_sounds, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (num_sounds)
		*num_sounds = r.n_sounds;
	if (r.n_sounds <= 0)
		return (0);
	*ui_sounds = (Mix_Chunk **)malloc(sizeof(Mix_Chunk *) * r.n_sounds);
	if (*ui_sounds == NULL)
		return (0);
	r.i = -1;
	while (++r.i < r.n_sounds)
		(*ui_sounds)[r.i] = NULL;
	r.i = -1;
	while (++r.i < r.n_sounds)
	{
		if (!read_allocsound(fd, ui_sounds, r))
			return (0);
	}
	return (1);
}
