/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_items_load_img.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:12:12 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/04 18:12:14 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void			player_init_rect_4(t_player_items *p_i)
{
	p_i->ui_rect[UI_RECT_L_M] = (SDL_Rect){334, 62, 100, 78};
	p_i->ui_rect[UI_RECT_L_E] = (SDL_Rect){435, 62, 100, 78};
	p_i->ui_rect[UI_RECT_L_O] = (SDL_Rect){132, 154, 100, 78};
	p_i->ui_rect[UI_RECT_L_V] = (SDL_Rect){233, 154, 100, 78};
	p_i->ui_rect[UI_RECT_L_E_BIS] = (SDL_Rect){334, 154, 100, 78};
	p_i->ui_rect[UI_RECT_L_R] = (SDL_Rect){435, 154, 100, 78};
	p_i->ui_rect[UI_RECT_L_E_E] = (SDL_Rect){0, 345, 48, 37};
	p_i->ui_rect[UI_RECT_L_N_E] = (SDL_Rect){49, 345, 48, 37};
	p_i->ui_rect[UI_RECT_L_T_E] = (SDL_Rect){98, 345, 48, 37};
	p_i->ui_rect[UI_RECT_L_E2_E] = (SDL_Rect){147, 345, 48, 37};
	p_i->ui_rect[UI_RECT_L_R_E] = (SDL_Rect){196, 345, 48, 37};
	p_i->ui_rect[UI_RECT_L_T_T] = (SDL_Rect){292, 345, 48, 37};
	p_i->ui_rect[UI_RECT_L_O_T] = (SDL_Rect){341, 345, 48, 37};
	p_i->ui_rect[UI_RECT_L_R_R] = (SDL_Rect){439, 345, 48, 37};
	p_i->ui_rect[UI_RECT_L_E_R] = (SDL_Rect){488, 345, 48, 37};
	p_i->ui_rect[UI_RECT_L_T_R] = (SDL_Rect){537, 345, 48, 37};
	p_i->ui_rect[UI_RECT_L_R2_R] = (SDL_Rect){586, 345, 48, 37};
	p_i->ui_rect[UI_RECT_L_Y_R] = (SDL_Rect){635, 345, 48, 37};
	p_i->ui_rect[UI_RECT_KEY_HAND] = (SDL_Rect){340, 680, 0, 0};
}

static void			player_init_rect_3(t_player_items *p_i)
{
	p_i->ui_rect[UI_RECT_NUM_1] = (SDL_Rect){24, 645, 0, 0};
	p_i->ui_rect[UI_RECT_NUM_2] = (SDL_Rect){43, 645, 0, 0};
	p_i->ui_rect[UI_RECT_NUM_3] = (SDL_Rect){26, 644, 0, 0};
	p_i->ui_rect[UI_RECT_AMMO_PANNEL] = (SDL_Rect){5 +
		p_i->ui_surface[UI_AMMO_PANNEL]->w + 1, WIN_HEIGHT -
			p_i->ui_surface[UI_AMMO_PANNEL]->h - 5, 0, 0};
	p_i->ui_rect[UI_RECT_NUM_4] = (SDL_Rect){75, 644, 0, 0};
	p_i->ui_rect[UI_RECT_NUM_5] = (SDL_Rect){86, 645, 0, 0};
	p_i->ui_rect[UI_RECT_NUM_6] = (SDL_Rect){105, 645, 0, 0};
	p_i->ui_rect[UI_RECT_NUM_7] = (SDL_Rect){88, 644, 0, 0};
	p_i->ui_rect[UI_RECT_NUM_8] = (SDL_Rect){168, 661, 0, 0};
	p_i->ui_rect[UI_RECT_NUM_9] = (SDL_Rect){174, 661, 0, 0};
	p_i->ui_rect[UI_RECT_NUM_10] = (SDL_Rect){182, 661, 0, 0};
	p_i->ui_rect[UI_RECT_NUM_11] = (SDL_Rect){192, 661, 0, 0};
	p_i->ui_rect[UI_RECT_INV_PANNEL] = (SDL_Rect){5 +
		p_i->ui_surface[UI_AMMO_PANNEL]->w * 2 + 2, WIN_HEIGHT -
			p_i->ui_surface[UI_INV_PANNEL]->h - 5, 0, 0};
	p_i->ui_rect[UI_RECT_JET_PACK] = (SDL_Rect){140, 643, 0, 0};
	p_i->ui_rect[UI_RECT_ON_JP_LED] = (SDL_Rect){167, 643, 0, 0};
	p_i->ui_rect[UI_RECT_OFF_JP_LED] = (SDL_Rect){167, 643, 0, 0};
	p_i->ui_rect[UI_RECT_KEY] = (SDL_Rect){10, 595, 0, 0};
	p_i->ui_rect[UI_RECT_L_G] = (SDL_Rect){132, 62, 100, 78};
	p_i->ui_rect[UI_RECT_L_A] = (SDL_Rect){233, 62, 100, 78};
	player_init_rect_4(p_i);
}

static void			player_init_rect_2(t_player_items *p_i)
{
	p_i->ui_rect[UI_RECT_GUN_LOAD_3] = (SDL_Rect){WIN_HEIGHT -
		p_i->ui_surface[UI_GUN_LOAD_2]->w - 15, WIN_HEIGHT -
			p_i->ui_surface[UI_GUN_LOAD_3]->h + 15, 0, 0};
	p_i->ui_rect[UI_RECT_GUN_LOAD_4] = (SDL_Rect){WIN_WIDTH / 2
		- p_i->ui_surface[UI_GUN_LOAD_4]->w / 2 + 40, WIN_HEIGHT -
			p_i->ui_surface[UI_GUN_LOAD_4]->h, 0, 0};
	p_i->ui_rect[UI_RECT_GUN_LOAD_5] = (SDL_Rect){WIN_WIDTH -
		p_i->ui_surface[UI_GUN_LOAD_5]->w - 50, WIN_HEIGHT -
			p_i->ui_surface[UI_GUN_LOAD_5]->h, 0, 0};
	p_i->ui_rect[UI_RECT_RPG_1] = (SDL_Rect){WIN_WIDTH -
		p_i->ui_surface[UI_RPG_1]->w + 20, WIN_HEIGHT -
			p_i->ui_surface[UI_RPG_1]->h + 10, 0, 0};
	p_i->ui_rect[UI_RECT_RPG_2] = (SDL_Rect){555, 583, 0, 0};
	p_i->ui_rect[UI_RECT_RPG_3] = (SDL_Rect){539, 569, 0, 0};
	p_i->ui_rect[UI_RECT_SCOOP_1] = (SDL_Rect){WIN_WIDTH / 2
		- p_i->ui_surface[UI_SCOOP_1]->w / 2, WIN_HEIGHT / 2 -
			p_i->ui_surface[UI_SCOOP_1]->h / 2, 0, 0};
	p_i->ui_rect[UI_RECT_SCOOP_2] = (SDL_Rect){WIN_WIDTH / 2
		- p_i->ui_surface[UI_SCOOP_2]->w / 2, WIN_HEIGHT / 2 -
			p_i->ui_surface[UI_SCOOP_2]->h / 2, 0, 0};
	p_i->ui_rect[UI_RECT_HEALTH_PANNEL] = (SDL_Rect){5, WIN_HEIGHT
		- p_i->ui_surface[UI_HEALTH_PANNEL]->h - 5, 0, 0};
	p_i->ui_rect[UI_RECT_NUM_0] = (SDL_Rect){13, 644, 0, 0};
	player_init_rect_3(p_i);
}

int					player_init_rect(t_engine *eng)
{
	t_player_items	*p_i;

	p_i = &eng->p_i;
	p_i->ui_rect[UI_RECT_GUN] = (SDL_Rect){WIN_WIDTH / 2 -
		p_i->ui_surface[UI_GUN]->w / 2 + 40, WIN_HEIGHT -
			p_i->ui_surface[UI_GUN]->h + 20, 0, 0};
	p_i->ui_rect[UI_RECT_GUN_SHOOT_1] = (SDL_Rect){WIN_WIDTH / 2 -
		p_i->ui_surface[UI_GUN_SHOOT_1]->w / 2 + 40, WIN_HEIGHT -
			p_i->ui_surface[UI_GUN_SHOOT_1]->h + 20, 0, 0};
	p_i->ui_rect[UI_RECT_GUN_SHOOT_2] = (SDL_Rect){WIN_WIDTH / 2 -
		p_i->ui_surface[UI_GUN_SHOOT_2]->w / 2 + 40, WIN_HEIGHT -
			p_i->ui_surface[UI_GUN_SHOOT_2]->h + 20, 0, 0};
	p_i->ui_rect[UI_RECT_GUN_LOAD_1] = (SDL_Rect){WIN_WIDTH / 2 -
		p_i->ui_surface[UI_GUN_LOAD_1]->w / 2 + 50, WIN_HEIGHT -
			p_i->ui_surface[UI_GUN_LOAD_1]->h, 0, 0};
	p_i->ui_rect[UI_RECT_GUN_LOAD_2] = (SDL_Rect){WIN_WIDTH / 2 -
		p_i->ui_surface[UI_GUN_LOAD_2]->w / 2 + 150, WIN_HEIGHT -
			p_i->ui_surface[UI_GUN_LOAD_2]->h + 38, 0, 0};
	p_i->ui_rect[UI_RECT_GUN_LOAD_2_BIS] = (SDL_Rect){WIN_WIDTH -
		p_i->ui_surface[UI_GUN_LOAD_2]->w - 5, WIN_HEIGHT -
			p_i->ui_surface[UI_GUN_LOAD_2]->h - 35, 0, 0};
	player_init_rect_2(p_i);
	return (0);
}
