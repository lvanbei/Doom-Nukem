/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		load_assets0(t_ed *ed)
{
	ed->ed_textures[UI_PLAYER] = SDL_LoadBMP("res/duke_head.bmp");
	ed->ed_textures[UI_HEAL] = SDL_LoadBMP("res/heal.bmp");
	ed->ed_textures[UI_AMMO] = SDL_LoadBMP("res/ammo.bmp");
	ed->ed_textures[UI_MONSTER] = SDL_LoadBMP("res/monster.bmp");
	ed->ed_textures[UI_KEYCARD] = SDL_LoadBMP("res/key.bmp");
	ed->ed_textures[UI_DEADMONSTER] = SDL_LoadBMP("res/monster_dead.bmp");
	ed->ed_textures[UI_JETPACK_FUEL] = SDL_LoadBMP("res/jetfuel.bmp");
	ed->ed_textures[UI_FIREBALL] = SDL_LoadBMP("res/fireball.bmp");
	ed->ed_textures[UI_IMPACT] = SDL_LoadBMP("res/impact.bmp");
	ed->ed_textures[UI_RPG] = SDL_LoadBMP("res/rpg.bmp");
	ed->ed_textures[UI_MOUSE_ENDING] = SDL_LoadBMP("res/mouse_ending.bmp");
	ed->textures[0] = SDL_LoadBMP("res/metal2.bmp");
	ed->textures[1] = SDL_LoadBMP("res/red_brick.bmp");
	ed->textures[2] = SDL_LoadBMP("res/metal.bmp");
	ed->textures[3] = SDL_LoadBMP("res/gross_flat.bmp");
	ed->textures[4] = SDL_LoadBMP("res/grey_flat.bmp");
	ed->textures[5] = SDL_LoadBMP("res/darkmetal.bmp");
	ed->textures[6] = SDL_LoadBMP("res/blue_and_grey.bmp");
	ed->menu_surfaces[MENU_BACK_GROUND] = SDL_LoadBMP("./img/menu_bg.bmp");
	ed->menu_surfaces[MENU_START] = SDL_LoadBMP("./img/start.bmp");
	ed->menu_surfaces[MENU_SETTINGS] = SDL_LoadBMP("./img/settings.bmp");
	ed->menu_surfaces[MENU_EXIT] = SDL_LoadBMP("./img/exit.bmp");
	ed->menu_surfaces[MENU_EASY] = SDL_LoadBMP("./img/menu_easy.bmp");
	ed->menu_surfaces[MENU_MEDIUM] = SDL_LoadBMP("./img/menu_medium.bmp");
	ed->menu_surfaces[MENU_HARD] = SDL_LoadBMP("./img/menu_hard.bmp");
}

void		load_assets1(t_ed *ed)
{
	ed->menu_surfaces[MENU_SELECTOR_1] = SDL_LoadBMP("./img/selector1.bmp");
	ed->menu_surfaces[MENU_SELECTOR_2] = SDL_LoadBMP("./img/selector2.bmp");
	ed->menu_surfaces[MENU_SELECTOR_3] = SDL_LoadBMP("./img/selector3.bmp");
	ed->menu_surfaces[MENU_SELECTOR_4] = SDL_LoadBMP("./img/selector4.bmp");
	ed->menu_surfaces[MENU_SELECTOR_5] = SDL_LoadBMP("./img/selector5.bmp");
	ed->menu_surfaces[MENU_SELECTOR_6] = SDL_LoadBMP("./img/selector6.bmp");
	ed->menu_surfaces[MENU_SELECTOR_7] = SDL_LoadBMP("./img/selector7.bmp");
	ed->menu_surfaces[MENU_DOOR_UP] = SDL_LoadBMP("./img/menu_door_up.bmp");
	ed->menu_surfaces[MENU_DOOR_DOWN] = SDL_LoadBMP("./img/menu_door_down.bmp");
	ed->player_ui_surfaces[UI_HIT_ALPHA_RED] = SDL_CreateRGBSurface(0,
			WIN_WIDTH, WIN_HEIGHT, ed->surface->format->BitsPerPixel,
			ed->surface->format->Rmask, ed->surface->format->Gmask,
			ed->surface->format->Bmask, ed->surface->format->Amask);
	ed->player_ui_surfaces[UI_GET_ALPHA_GREEN] = SDL_CreateRGBSurface(0,
			WIN_WIDTH, WIN_HEIGHT, ed->surface->format->BitsPerPixel,
			ed->surface->format->Rmask, ed->surface->format->Gmask,
			ed->surface->format->Bmask, ed->surface->format->Amask);
	ed->player_ui_surfaces[UI_GUN] = SDL_LoadBMP("./img/gun.bmp");
	ed->player_ui_surfaces[UGS1] = SDL_LoadBMP("./img/gun_shoot_1.bmp");
	ed->player_ui_surfaces[UGS2] = SDL_LoadBMP("./img/gun_shoot_2.bmp");
	ed->player_ui_surfaces[UI_GUN_LOAD_1] = SDL_LoadBMP("./img/gun_load_1.bmp");
	ed->player_ui_surfaces[UI_GUN_LOAD_2] = SDL_LoadBMP("./img/gun_load_2.bmp");
	ed->player_ui_surfaces[UGL2BIS] = SDL_LoadBMP("./img/gun_load_2_bis.bmp");
	ed->player_ui_surfaces[UI_GUN_LOAD_3] = SDL_LoadBMP("./img/gun_load_3.bmp");
	ed->player_ui_surfaces[UI_GUN_LOAD_4] = SDL_LoadBMP("./img/gun_load_4.bmp");
}

void		load_assets2(t_ed *ed)
{
	ed->player_ui_surfaces[UI_GUN_LOAD_5] = SDL_LoadBMP("./img/gun_load_5.bmp");
	ed->player_ui_surfaces[UI_RPG_1] = SDL_LoadBMP("./img/rpg1.bmp");
	ed->player_ui_surfaces[UI_RPG_2] = SDL_LoadBMP("./img/rpg2.bmp");
	ed->player_ui_surfaces[UI_RPG_3] = SDL_LoadBMP("./img/rpg3.bmp");
	ed->player_ui_surfaces[UI_SCOOP_1] = SDL_LoadBMP("./img/scoop1.bmp");
	ed->player_ui_surfaces[UI_SCOOP_2] = SDL_LoadBMP("./img/scoop2.bmp");
	ed->player_ui_surfaces[UI_HEALTH_PANNEL] = SDL_LoadBMP("./img/health.bmp");
	ed->player_ui_surfaces[UI_AMMO_PANNEL] = SDL_LoadBMP("./img/ammo.bmp");
	ed->player_ui_surfaces[UI_INV_PANNEL] = SDL_LoadBMP("./img/inv.bmp");
	ed->player_ui_surfaces[UI_JET_PACK] = SDL_LoadBMP("./img/jet_pack.bmp");
	ed->player_ui_surfaces[UI_ON_JP_LED] = SDL_LoadBMP("./img/on.bmp");
	ed->player_ui_surfaces[UI_OFF_JP_LED] = SDL_LoadBMP("./img/off.bmp");
	ed->player_ui_surfaces[UI_PERCENT] = SDL_LoadBMP("./img/percent.bmp");
	ed->player_ui_surfaces[UI_NUMBER_0_0] = SDL_LoadBMP("./img/0.bmp");
	ed->player_ui_surfaces[UI_NUMBER_1_0] = SDL_LoadBMP("./img/1.bmp");
	ed->player_ui_surfaces[UI_NUMBER_2_0] = SDL_LoadBMP("./img/2.bmp");
	ed->player_ui_surfaces[UI_NUMBER_3_0] = SDL_LoadBMP("./img/3.bmp");
	ed->player_ui_surfaces[UI_NUMBER_4_0] = SDL_LoadBMP("./img/4.bmp");
	ed->player_ui_surfaces[UI_NUMBER_5_0] = SDL_LoadBMP("./img/5.bmp");
	ed->player_ui_surfaces[UI_NUMBER_6_0] = SDL_LoadBMP("./img/6.bmp");
	ed->player_ui_surfaces[UI_NUMBER_7_0] = SDL_LoadBMP("./img/7.bmp");
	ed->player_ui_surfaces[UI_NUMBER_8_0] = SDL_LoadBMP("./img/8.bmp");
	ed->player_ui_surfaces[UI_NUMBER_9_0] = SDL_LoadBMP("./img/9.bmp");
	ed->player_ui_surfaces[UI_NUMBER_0_10] = SDL_LoadBMP("./img/00.bmp");
	ed->player_ui_surfaces[UI_NUMBER_1_10] = SDL_LoadBMP("./img/11.bmp");
}

void		load_assets3(t_ed *ed)
{
	ed->player_ui_surfaces[UI_NUMBER_2_10] = SDL_LoadBMP("./img/22.bmp");
	ed->player_ui_surfaces[UI_NUMBER_3_10] = SDL_LoadBMP("./img/33.bmp");
	ed->player_ui_surfaces[UI_NUMBER_4_10] = SDL_LoadBMP("./img/44.bmp");
	ed->player_ui_surfaces[UI_NUMBER_5_10] = SDL_LoadBMP("./img/55.bmp");
	ed->player_ui_surfaces[UI_NUMBER_6_10] = SDL_LoadBMP("./img/66.bmp");
	ed->player_ui_surfaces[UI_NUMBER_7_10] = SDL_LoadBMP("./img/77.bmp");
	ed->player_ui_surfaces[UI_NUMBER_8_10] = SDL_LoadBMP("./img/88.bmp");
	ed->player_ui_surfaces[UI_NUMBER_9_10] = SDL_LoadBMP("./img/99.bmp");
	ed->player_ui_surfaces[UI_LETTER_G] = SDL_LoadBMP("./img/l_G.bmp");
	ed->player_ui_surfaces[UI_LETTER_A] = SDL_LoadBMP("./img/l_A.bmp");
	ed->player_ui_surfaces[UI_LETTER_M] = SDL_LoadBMP("./img/l_M.bmp");
	ed->player_ui_surfaces[UI_LETTER_E] = SDL_LoadBMP("./img/l_E.bmp");
	ed->player_ui_surfaces[UI_LETTER_O] = SDL_LoadBMP("./img/l_O.bmp");
	ed->player_ui_surfaces[UI_LETTER_V] = SDL_LoadBMP("./img/l_V.bmp");
	ed->player_ui_surfaces[UI_LETTER_R] = SDL_LoadBMP("./img/l_R.bmp");
	ed->player_ui_surfaces[UI_LETTER_N] = SDL_LoadBMP("./img/l_N.bmp");
	ed->player_ui_surfaces[UI_LETTER_T] = SDL_LoadBMP("./img/l_T.bmp");
	ed->player_ui_surfaces[UI_LETTER_Y] = SDL_LoadBMP("./img/l_Y.bmp");
	ed->player_ui_surfaces[UI_KEY] = SDL_LoadBMP("./res/key.bmp");
	ed->player_ui_surfaces[UI_KEY_HAND] = SDL_LoadBMP("./img/key_hand.bmp");
	ed->player_ui_surfaces[UI_KEYS_MENU] = SDL_LoadBMP("./img/keys_menu.bmp");
	ed->player_ui_surfaces[UI_WIN] = SDL_LoadBMP("./img/win.bmp");
}

void		load_assets(t_ed *ed)
{
	load_assets0(ed);
	load_assets1(ed);
	load_assets2(ed);
	load_assets3(ed);
	check_assets(ed);
	init_alpha_filter_surface(ed->player_ui_surfaces[UI_HIT_ALPHA_RED],
			(t_mask) {90, 255, 0, 0});
	init_alpha_filter_surface(ed->player_ui_surfaces[UI_GET_ALPHA_GREEN],
			(t_mask) {90, 0, 255, 0});
	load_assets4(ed);
	load_assets5(ed);
}
