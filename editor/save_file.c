/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:07:38 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/25 10:09:26 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int		write_texture(int fd,
		SDL_Surface *textures[NUM_TEXTURES], int i)
{
	if (write(fd, (void *)&textures[i]->w, sizeof(int)) != sizeof(int))
		return (0);
	if (write(fd, (void *)&textures[i]->h, sizeof(int)) != sizeof(int))
		return (0);
	if (write(fd, (void *)&textures[i]->pitch, sizeof(int)) != sizeof(int))
		return (0);
	if (write(fd, (void *)&textures[i]->format->BitsPerPixel,
				sizeof(uint8_t)) != sizeof(uint8_t))
		return (0);
	if (write(fd, (void *)&textures[i]->format->Rmask,
				sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (write(fd, (void *)&textures[i]->format->Gmask,
				sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (write(fd, (void *)&textures[i]->format->Bmask,
				sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (write(fd, (void *)&textures[i]->format->Amask,
				sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	if (write(fd, (void *)textures[i]->pixels, textures[i]->pitch *
				textures[i]->h) != textures[i]->pitch * textures[i]->h)
		return (0);
	return (1);
}

static int		write_textures(int fd, uint32_t num_textures,
		SDL_Surface *textures[NUM_TEXTURES])
{
	uint32_t i;

	if (write(fd, &num_textures, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	i = -1;
	while (++i < num_textures)
		if (!write_texture(fd, textures, i))
			return (0);
	return (1);
}

static int		write_audio(int fd, uint32_t num_sounds,
		Mix_Chunk *ui_sound[UI_SOUND_END])
{
	unsigned	i;

	if (write(fd, &num_sounds, sizeof(uint32_t)) != sizeof(uint32_t))
		return (0);
	i = -1;
	while (++i < num_sounds)
	{
		if (write(fd, (void *)&ui_sound[i]->alen,
					sizeof(uint32_t)) != sizeof(uint32_t))
			return (0);
		if (write(fd, ui_sound[i]->abuf, ui_sound[i]->alen)
				!= ui_sound[i]->alen)
			return (0);
	}
	return (1);
}

void			save_file2(int fd, t_ed *ed)
{
	if (!write_player(fd, &ed->player))
		abort_error(ed, "couldn't write player\n");
	if (!write_things(fd, ed->num_things, ed->things))
		abort_error(ed, "couldn't write things\n");
	if (!write_textures(fd, NUM_TEXTURES, ed->textures))
		abort_error(ed, "couldn't write texture\n");
	if (!write_textures(fd, UI_END, ed->ed_textures))
		abort_error(ed, "couldn't write ed textures\n");
	if (!write_textures(fd, MENU_SURFACE_END, ed->menu_surfaces))
		abort_error(ed, "couldn't write menu textures\n");
	if (!write_textures(fd, UI_SURFACES_END, ed->player_ui_surfaces))
		abort_error(ed, "couldn't write player surfaces\n");
	if (!write_audio(fd, UI_SOUND_END, ed->ui_sound))
		abort_error(ed, "couldn't write audio\n");
	ft_printf("saved map to: %s\n", ed->filename);
}

void			save_file(t_ed *ed)
{
	int fd;

	wall_update_checks(ed);
	if (!safety_checks(ed))
		return ;
	thing_update_checks(ed);
	fd = open(ed->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		abort_error(ed, "Couldn't open file for saving: %s\n");
	if (!write_code(fd))
		abort_error(ed, "couldn't write magic code\n");
	if (!write_walls(fd, ed->num_walls, ed->walls))
		abort_error(ed, "couldn't write walls\n");
	if (!write_sectors(fd, ed->num_sectors, ed->sectors))
		abort_error(ed, "couldn't write sectors\n");
	save_file2(fd, ed);
	close(fd);
}
