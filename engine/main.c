/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:57:43 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/25 09:44:39 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	init_assets_to_null(t_engine *eng)
{
	eng->walls = NULL;
	eng->sectors = NULL;
	eng->things = NULL;
	eng->textures = NULL;
	eng->thing_textures = NULL;
	eng->menu.surfaces = NULL;
	eng->p_i.ui_surface = NULL;
	eng->p_i.ui_sound = NULL;
}

int		main(int argc, char **argv)
{
	static t_engine eng;

	if (argc != 2)
		abort_error(NULL, "usage: ./doom_nukem [level_filename]");
	init_assets_to_null(&eng);
	if (!read_font_table(eng.font_table))
		abort_error(NULL, "font table\n");
	sdl_init_audio();
	if (access(argv[1], R_OK | W_OK) == 0)
		load_file(&eng, argv[1]);
	else
		abort_error(NULL, "file: %s doesn't exist\n", argv[1]);
	sdl_init(&eng);
	menu(&eng, &eng.menu);
	player_init_rect(&eng);
	doom_loop(&eng);
	free_assets(&eng);
	sdl_shutdown(eng.window);
	return (0);
}
