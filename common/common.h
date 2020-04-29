/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:30:09 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:13:24 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

# include <fcntl.h>
# include <SDL.h>
# include "SDL_mixer.h"
# include <unistd.h>

# include "ft_printf/ft_printf.h"

# define YELLOW 0xFFFFFF00
# define GREEN 0xFF00FF00
# define WHITE 0xFFFFFFFF
# define BLUE  0xFF0000FF
# define RED 0xFFFF0000
# define CYAN 0xFF00FFFF
# define DIMGRAY 0xFF696969
# define TEAL 0xFF008080

# define PLAYER_HEIGHT34 0.75f
# define PLAYER_HEIGHT 1.0f
# define MONSTER_HEIGHT 2.0f
# define AMMO_HEIGHT 0.5f
# define HEAL_HEIGHT 0.8f
# define DEADMONSTER_HEIGHT 0.5f
# define KEY_HEIGHT 0.5f
# define JETPACK_HEIGHT 0.5f
# define FIREBALL_HEIGHT 0.25f
# define IMPACT_HEIGHT 0.05f
# define RPG_HEIGHT 0.3f
# define MOUSE_ENDING_HEIGHT 1.4f

# define MONSTER_HEALTH 10.0f

# define MAX_NUM_PROJECTILES 5
# define MAX_WALLS 1024
# define MAX_SECTORS 64
# define MAX_THINGS 128

enum					e_ui_surfaces
{
	UI_NUMBER_0_0 = 0,
	UI_NUMBER_1_0,
	UI_NUMBER_2_0,
	UI_NUMBER_3_0,
	UI_NUMBER_4_0,
	UI_NUMBER_5_0,
	UI_NUMBER_6_0,
	UI_NUMBER_7_0,
	UI_NUMBER_8_0,
	UI_NUMBER_9_0,
	UI_NUMBER_0_10,
	UI_NUMBER_1_10,
	UI_NUMBER_2_10,
	UI_NUMBER_3_10,
	UI_NUMBER_4_10,
	UI_NUMBER_5_10,
	UI_NUMBER_6_10,
	UI_NUMBER_7_10,
	UI_NUMBER_8_10,
	UI_NUMBER_9_10,
	UI_HIT_ALPHA_RED,
	UI_GUN,
	UI_GUN_SHOOT_1,
	UI_GUN_SHOOT_2,
	UI_GUN_LOAD_1,
	UI_GUN_LOAD_2,
	UI_GUN_LOAD_2_BIS,
	UI_GUN_LOAD_3,
	UI_GUN_LOAD_4,
	UI_GUN_LOAD_5,
	UI_RPG_1,
	UI_RPG_2,
	UI_RPG_3,
	UI_SCOOP_1,
	UI_SCOOP_2,
	UI_HEALTH_PANNEL,
	UI_AMMO_PANNEL,
	UI_INV_PANNEL,
	UI_JET_PACK,
	UI_ON_JP_LED,
	UI_OFF_JP_LED,
	UI_PERCENT,
	UI_GET_ALPHA_GREEN,
	UI_KEY,
	UI_LETTER_G,
	UI_LETTER_A,
	UI_LETTER_M,
	UI_LETTER_E,
	UI_LETTER_O,
	UI_LETTER_V,
	UI_LETTER_R,
	UI_LETTER_T,
	UI_LETTER_Y,
	UI_LETTER_N,
	UI_KEY_HAND,
	UI_KEYS_MENU,
	UI_WIN,
	UI_SURFACES_END,
};

enum					e_menu_surfaces
{
	MENU_BACK_GROUND = 0,
	MENU_START,
	MENU_SETTINGS,
	MENU_EXIT,
	MENU_EASY,
	MENU_MEDIUM,
	MENU_HARD,
	MENU_SELECTOR_1,
	MENU_SELECTOR_2,
	MENU_SELECTOR_3,
	MENU_SELECTOR_4,
	MENU_SELECTOR_5,
	MENU_SELECTOR_6,
	MENU_SELECTOR_7,
	MENU_DOOR_UP,
	MENU_DOOR_DOWN,
	MENU_SURFACE_END,
};

enum					e_ui_sounds
{
	UI_SOUND_GUN_SHOOT = 0,
	UI_SOUND_GUN_RELOAD_1,
	UI_SOUND_RPG_SHOOT,
	UI_SOUND_JP_1,
	UI_SOUND_JP_2,
	UI_SOUND_JP_3,
	UI_SOUND_GET_ITEM,
	UI_SOUND_MENU,
	UI_SOUND_EXPLODE,
	UI_SOUND_DOORMOVE,
	UI_SOUND_BUTTON,
	UI_SOUND_DIE,
	UI_SOUND_END,
};

typedef struct			s_v2
{
	int				x;
	int				y;
}						t_v2;

typedef struct			s_v2f
{
	double			x;
	double			y;
}						t_v2f;

typedef struct			s_v3
{
	int				x;
	int				y;
	int				z;
}						t_v3;

typedef struct			s_v3f
{
	double			x;
	double			y;
	double			z;
}						t_v3f;

typedef struct			s_line2
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
}						t_line2;

typedef struct			s_line2f
{
	double			x0;
	double			y0;
	double			x1;
	double			y1;
}						t_line2f;

# define WALL_FLAG_OPEN 0x1
# define WALL_FLAG_CLOSED 0x2

typedef struct			s_wall
{
	int				x;
	int				y;
	int				next_wall;
	short			next_sector;
	double			door_height;
	uint8_t			flags;
	int8_t			b_texture;
	int8_t			m_texture;
	int8_t			t_texture;
}						t_wall;

typedef struct			s_sector
{
	int				start_wall;
	int				num_walls;
	double			floor_height;
	double			ceiling_height;
	int8_t			floor_texture;
	int8_t			ceiling_texture;
}						t_sector;

enum					e_thing
{
	TH_NONE = -1,
	TH_PLAYER,
	TH_HEAL,
	TH_AMMO,
	TH_MONSTER,
	TH_KEY,
	TH_JETPACK_FUEL,
	TH_RPG,
	TH_MOUSE_ENDING,
	TH_DEADMONSTER,
	TH_FIREBALL,
	TH_IMPACT,
	TH_END,
};

# define TH_VISIBLE_END TH_DEADMONSTER

typedef struct			s_thing
{
	enum e_thing	type;
	double			x;
	double			y;
	double			z;
	union
	{
		double			yaw;
		double			health;
		int				projectile_id;
	}				attr;
	double			zv;
	int				sector;
}						t_thing;

typedef struct			s_text
{
	char			(*font_table)[128][8];
	int				x;
	int				y;
	int				color;
}						t_text;

int						print_to_screen(SDL_Surface *screen,
t_text t, char *format, ...);
int						verify_code(int fd);
int						read_player(int fd, t_thing *player);

double					f_clamp(double min, double a, double max);
int						i_min(int a, int b);
int						i_max(int a, int b);
double					line_len(double x0, double y0, double x1, double y1);
double					l_line_len(const t_line2f *l);
double					w2p_dist(const t_wall *w1, const t_wall *w2, double p_x,
double p_y);
double					dist2(double x0, double y0, double x1, double y1);

void					*slow_memcpy(void *restrict dst,
const void *restrict src, size_t n);
void					*slow_memset(void *dst, int c, size_t n);
void					*slow_bzero(void *dst, size_t n);
void					*slow_memmove(void *dst, const void *src, size_t n);
int						slow_strcmp(const char *s1, const char *s2);
int						read_font_table(char font_table[128][8]);
#endif
