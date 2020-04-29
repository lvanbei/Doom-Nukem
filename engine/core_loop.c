/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:20:30 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/04 12:46:50 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void				init_thing_dimensions(t_engine *eng)
{
	eng->thing_height[TH_PLAYER] = PLAYER_HEIGHT;
	eng->thing_width[TH_MONSTER] = 1.4f;
	eng->thing_height[TH_MONSTER] = MONSTER_HEIGHT;
	eng->thing_width[TH_AMMO] = 1.0f;
	eng->thing_height[TH_AMMO] = AMMO_HEIGHT;
	eng->thing_width[TH_HEAL] = 1.0f;
	eng->thing_height[TH_HEAL] = HEAL_HEIGHT;
	eng->thing_width[TH_DEADMONSTER] = 1.3f;
	eng->thing_height[TH_DEADMONSTER] = DEADMONSTER_HEIGHT;
	eng->thing_width[TH_KEY] = 1.0f;
	eng->thing_height[TH_KEY] = KEY_HEIGHT;
	eng->thing_width[TH_JETPACK_FUEL] = 0.5f;
	eng->thing_height[TH_JETPACK_FUEL] = JETPACK_HEIGHT;
	eng->thing_width[TH_FIREBALL] = FIREBALL_HEIGHT * 1.1f;
	eng->thing_height[TH_FIREBALL] = FIREBALL_HEIGHT;
	eng->thing_width[TH_IMPACT] = IMPACT_HEIGHT * 1.1f;
	eng->thing_height[TH_IMPACT] = IMPACT_HEIGHT;
	eng->thing_width[TH_RPG] = RPG_HEIGHT * 3.2f;
	eng->thing_height[TH_RPG] = RPG_HEIGHT;
	eng->thing_height[TH_MOUSE_ENDING] = MOUSE_ENDING_HEIGHT;
	eng->thing_width[TH_MOUSE_ENDING] = MOUSE_ENDING_HEIGHT * 0.84f;
}

static inline void	init_vars(t_engine *eng, t_doom_loop *dl)
{
	init_thing_dimensions(eng);
	eng->num_projectiles = 0;
	eng->projectile_queue_idx = 0;
	eng->doors_opening[0] = -1;
	init_player_items_var(&eng->p_i);
	eng->fireball_damage = FIREBALL_DAMAGE / (double)eng->menu.game_hardless;
	eng->bullet_damage = BULLET_DAMAGE / (double)eng->menu.game_hardless;
	dl->last_time = 0;
	dl->current_time = 0;
	dl->pause_game = 0;
	dl->delta = 0;
	dl->f_delta = 0.0f;
}

static inline int	event_loop(t_engine *eng, t_doom_loop *dl)
{
	handle_mouse_event(eng, &dl->e);
	if (dl->e.type == SDL_QUIT || eng->key_states[SDL_SCANCODE_ESCAPE])
		return (0);
	if (dl->e.type == SDL_KEYDOWN && dl->e.key.keysym.sym == SDLK_F3
			&& !dl->e.key.repeat)
		eng->r_flags ^= RF_DEBUG_HUD;
	if (dl->e.type == SDL_KEYDOWN && dl->e.key.keysym.sym == SDLK_F6
	&& !dl->e.key.repeat && (int)eng->p_i.life > 0)
		dl->pause_game = !dl->pause_game;
	if (dl->e.type == SDL_KEYDOWN && dl->e.key.keysym.sym == SDLK_j
			&& !dl->e.key.repeat)
		eng->p_i.jet_pack_led ^= 1;
	if (dl->e.type == SDL_KEYDOWN && dl->e.key.keysym.scancode ==
			SDL_SCANCODE_LSHIFT && !dl->e.key.repeat)
		key_shoot(eng);
	player_items_event(eng, &dl->e);
	return (1);
}

static inline void	update_loop(t_engine *eng, t_doom_loop *dl)
{
	update_doors(eng, dl->f_delta);
	update_player(eng, eng->key_states, dl->f_delta);
	update_things(eng, dl->f_delta);
	slow_bzero(eng->surface->pixels, WIN_WIDTH * WIN_HEIGHT * 4);
	render(eng);
	player_items_get(eng);
	ui_audio(&eng->p_i);
	update_percent_jp(&eng->p_i, dl->delta);
	change_gun(eng, &eng->p_i, dl->delta);
	move_gun(&eng->p_i, eng->key_states, dl->delta);
	move_rpg(&eng->p_i, eng->key_states, dl->delta);
	key_hand(eng, &eng->p_i, dl->delta);
	player_dammages(eng, &eng->p_i);
	win(eng, &dl->pause_game);
	blit_player_items(eng, &eng->p_i, dl->delta, &dl->pause_game);
}

void				doom_loop(t_engine *eng)
{
	t_doom_loop dl;

	init_vars(eng, &dl);
	while (1)
	{
		while (SDL_PollEvent(&dl.e))
		{
			if (!event_loop(eng, &dl))
				return ;
		}
		dl.current_time = SDL_GetTicks();
		dl.delta = (dl.current_time - dl.last_time);
		if (dl.delta > 200)
			dl.delta = 200;
		dl.f_delta = dl.delta / 1000.0f;
		dl.last_time = dl.current_time;
		if (!dl.pause_game)
			update_loop(eng, &dl);
		display_menu(eng, &eng->p_i, dl.pause_game);
		game_over(eng, &eng->p_i, dl.delta);
		display_win(eng);
		SDL_UpdateWindowSurface(eng->window);
	}
}
