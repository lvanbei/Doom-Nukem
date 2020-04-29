/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:02 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 10:47:36 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void				init_assets_to_null(t_ed *ed)
{
	int i;

	i = -1;
	while (++i < UI_END)
		ed->ed_textures[i] = NULL;
	i = -1;
	while (++i < NUM_TEXTURES)
		ed->textures[i] = NULL;
	i = -1;
	while (++i < MENU_SURFACE_END)
		ed->menu_surfaces[i] = NULL;
	i = -1;
	while (++i < UI_SURFACES_END)
		ed->player_ui_surfaces[i] = NULL;
	i = -1;
	while (++i < UI_SOUND_END)
		ed->ui_sound[i] = NULL;
}

static inline void	main2(t_ed *ed)
{
	sdl_init(ed);
	if (!read_font_table(ed->font_table))
		abort_error(ed, "font table\n");
	core_loop(ed);
	free_assets(ed);
	init_assets_to_null(ed);
	sdl_shutdown(ed->window);
}

int					main(int argc, char **argv)
{
	static t_ed	ed;
	int			len;

	if (argc != 2)
		abort_error(NULL, "usage: ./vis_ed [level_filename/output_filename]");
	len = ft_strlen(argv[1]);
	if (len > MAX_FILENAME_LEN)
		abort_error(NULL, "filename can't exceed: %u characters\n",
				MAX_FILENAME_LEN);
	init_assets_to_null(&ed);
	ft_strcpy(ed.filename, argv[1]);
	if (access(argv[1], R_OK | W_OK) == 0)
		load_file(&ed);
	else
	{
		ed.num_walls = 0;
		ed.num_sectors = 0;
		ed.num_things = 0;
		ed.player_set = 0;
	}
	main2(&ed);
	return (0);
}
