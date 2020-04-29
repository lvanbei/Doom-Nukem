/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:47:46 by hde-moff          #+#    #+#             */
/*   Updated: 2020/03/01 19:46:43 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "common.h"
# include <time.h>
# include <pthread.h>

# define WIN_WIDTH 680
# define WIN_HEIGHT 680
# define CH ceiling_height
# define CT ceiling_texture
# define FT floor_texture
# define FH floor_height
# define PPS player_pitch_shift

# define MAX_PVWALLS 1024
# define MAX_PVSPRITES 256
# define MAX_BUNCHES 1024
# define MAX_SCANSECTS 64
# define WIDTH_CENTER 340
# define HEIGHT_CENTER 340
# define HSCALE  340
# define VSCALE 340
# define R_WALL_HEIGHT 340

# define METERS_PER_SECOND 5.0f
# define CROUCH_SPEED 0.1f
# define JUMP_STARTVELOCITY 2.0f
# define JETPACK_THRUST_VELOCITY 0.75f
# define TERMINAL_VELOCITY -5.0f
# define STEP_HEIGHT 0.25f
# define PLAYER_CEILING_CLIP 0.25f
# define PROJECTILE_METERS_PER_SECOND 13.0f
# define BULLET_DAMAGE 5.0f
# define FIREBALL_DAMAGE 10.0f

# define MONSTER_SPOT_RADIUS 7.5f
# define MONSTER_DAMAGE_RADIUS 0.5f
# define MONSTER_METERS_PER_SECOND 2.75f

# define MAX_PITCH 226
# define ARROW_X_RAD_PER_S M_PI
# define ARROW_Y_PX_PER_S 1000.0f

# define MOUSE_X_RAD_PER_PX 0.020944f
# define MOUSE_Y_PX_PER_PX 5

# define P 0
# define ROTATED 1

# define MAX_CLIPLINES 75
# define MAX_CLIPSECTS 5
# define MAX_CLIPSLIDES 3
# define WD 0.125f
# define WALLDIST 0.125f

# define CHANGEGUNTIMER 0.3
# define TIMER_MOVE_GUN 0.2

# define NUM_IMG 57
# define NUM_RECT 54
# define NUM_ITEM 4
# define NUM_SOUND 9
# define NUM_MENU_RECT 15

# define DOOR_METER_PER_S 2.5f
# define DELTA_GUN_X 40
# define DELTA_GUN_Y 20
# define DELTA_RPG_X 20
# define DELTA_RPG_Y 10

enum					e_ui_rects
{
	UI_RECT_NUM_0 = 0,
	UI_RECT_NUM_1,
	UI_RECT_NUM_2,
	UI_RECT_NUM_3,
	UI_RECT_NUM_4,
	UI_RECT_NUM_5,
	UI_RECT_NUM_6,
	UI_RECT_NUM_7,
	UI_RECT_NUM_8,
	UI_RECT_NUM_9,
	UI_RECT_NUM_10,
	UI_RECT_NUM_11,
	UI_RECT_GUN,
	UI_RECT_GUN_SHOOT_1,
	UI_RECT_GUN_SHOOT_2,
	UI_RECT_GUN_LOAD_1,
	UI_RECT_GUN_LOAD_2,
	UI_RECT_GUN_LOAD_2_BIS,
	UI_RECT_GUN_LOAD_3,
	UI_RECT_GUN_LOAD_4,
	UI_RECT_GUN_LOAD_5,
	UI_RECT_RPG_1,
	UI_RECT_RPG_2,
	UI_RECT_RPG_3,
	UI_RECT_SCOOP_1,
	UI_RECT_SCOOP_2,
	UI_RECT_HEALTH_PANNEL,
	UI_RECT_AMMO_PANNEL,
	UI_RECT_INV_PANNEL,
	UI_RECT_JET_PACK,
	UI_RECT_ON_JP_LED,
	UI_RECT_OFF_JP_LED,
	UI_RECT_KEY,
	UI_RECT_L_G,
	UI_RECT_L_A,
	UI_RECT_L_M,
	UI_RECT_L_E,
	UI_RECT_L_O,
	UI_RECT_L_V,
	UI_RECT_L_E_BIS,
	UI_RECT_L_R,
	UI_RECT_L_E_E,
	UI_RECT_L_N_E,
	UI_RECT_L_T_E,
	UI_RECT_L_E2_E,
	UI_RECT_L_R_E,
	UI_RECT_L_T_T,
	UI_RECT_L_O_T,
	UI_RECT_L_R_R,
	UI_RECT_L_E_R,
	UI_RECT_L_T_R,
	UI_RECT_L_R2_R,
	UI_RECT_L_Y_R,
	UI_RECT_KEY_HAND,
};

enum					e_ui_items
{
	UI_ITEM_AMMO = 0,
	UI_ITEM_KEY,
	UI_ITEM_JET_PACK,
	UI_ITEM_RPG,
};

enum					e_menu_rects
{
	MENU_RECT_START,
	MENU_RECT_SETTINGS,
	MENU_RECT_EXIT,
	MENU_RECT_EASY,
	MENU_RECT_MEDIUM,
	MENU_RECT_HARD,
	MENU_RECT_DOOR_UP,
	MENU_RECT_DOOR_DOWN,
	MENU_RECT_SELECTOR_1,
	MENU_RECT_SELECTOR_2,
	MENU_RECT_SELECTOR_3,
	MENU_RECT_SELECTOR_4,
	MENU_RECT_SELECTOR_5,
	MENU_RECT_SELECTOR_6,
	MENU_RECT_SELECTOR_7,
};

typedef struct			s_player_items
{
	SDL_Surface		**ui_surface;
	SDL_Rect		ui_rect[NUM_RECT];
	SDL_Surface		*ui_mm_surface[NUM_ITEM];
	SDL_Rect		ui_mm_rect[NUM_ITEM];
	Mix_Chunk		**ui_sound;
	int				inv_items[NUM_ITEM];
	int				shoot_led;
	int				rpg_shoot_led;
	int				gun_load_led;
	int				item_led;
	int				life_led;
	double			life;
	int				ammo_gun;
	int				ammo_rpg;
	int				game_hardless;
	int				change_gun_led;
	double			delta_min;
	int				find_item_led;
	int				key;
	int				gun_number;
	int				gun_down;
	double			percent_jp;
	int				jet_pack_led;
	double			var_height_gun_plus;
	double			var_height_gun_min;
	double			var_height_rpg_plus;
	double			var_height_rpg_min;
	double			var_width_rpg;
	double			var_height_rpg;
	double			var_width_gun;
	double			var_height_gun;
	double			timer_gun;
	double			timer_rpg;
	int				ammo_per_load_gun;
	int				pos_gun_x;
	int				pos_gun_y;
	int				pos_rpg_x;
	int				pos_rpg_y;
	double			spawn_x;
	double			spawn_y;
	int				key_hand;
	int				key_on;
	int				win;
	int				activate_doors;
}						t_player_items;

typedef struct			s_menu
{
	SDL_Surface		**surfaces;
	SDL_Rect		rect[NUM_MENU_RECT];
	int				which_menu;
	int				x;
	int				y;
	int				go_game;
	int				game_hardless;
	int				ret;
	int				delta;
	double			timer_plus;
	double			timer_min;
}						t_menu;

typedef struct			s_doom_loop
{
	int			last_time;
	int			current_time;
	SDL_Event	e;
	int			pause_game;
	int			delta;
	double		f_delta;
}						t_doom_loop;

typedef struct			s_updatep_struct
{
	double		zv;
	uint8_t		on_ground;
	t_v2f		vec;
	int			jp_available;
}						t_updatep_struct;

typedef struct			s_walldist
{
	double	x0;
	double	y0;
	double	x1;
	double	y1;
	double	px;
	double	py;
}						t_walldist;

typedef struct			s_box
{
	double	xmin;
	double	ymin;
	double	xmax;
	double	ymax;
}						t_box;

typedef struct			s_see_player
{
	t_box		b;
	t_thing		monster;
	int			i;
	t_line2f	w;
	t_v2f		p;
}						t_see_player;

typedef struct			s_line_inter
{
	double	s1_x;
	double	s1_y;
	double	s2_x;
	double	s2_y;
	double	s;
	double	t;
}						t_line_inter;

typedef struct			s_pushmove
{
	int			last_wall;
	double		base_height;
	int			i;
	t_line2f	w;
	double		nx;
	double		ny;
	double		wall_len;
	int			tries;
}						t_pushmove;

# define CLIPMOVE_F_PROJ 0x1

typedef struct			s_clipbox
{
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
	double	xv;
	double	yv;
	double	zv;
}						t_clipbox;

typedef struct			s_cliplines
{
	t_line2f	lines[MAX_CLIPLINES];
	int			num_lines;
	int			clipsects[MAX_CLIPSECTS];
	int			num_clipsects;
	int16_t		line_thing_id[MAX_CLIPLINES];
}						t_cliplines;

typedef struct			s_clipmove_struct
{
	t_clipbox		cb;
	t_cliplines		cl;
	double			radius;
	double			x;
	double			y;
	double			z;
	double			tmp_x;
	double			tmp_y;
	double			goalx;
	double			goaly;
	double			center_x;
	double			center_y;
	double			l1;
	double			l2;
	double			l3;
	int				i2;
	int				i3;
	int				hitwall;
	int				cnt;
	int				j;
	int				hitwalls[MAX_CLIPSLIDES];
	int				ret;
	int				hit;
	double			wx;
	double			wy;
	int				i;
	int				flags;
}						t_clipmove_struct;

typedef struct			s_fillcliplines
{
	int			start_wall;
	int			end_wall;
	int			clipsect_idx;
	int			clipline_idx;
	int			j;
	double		dx;
	double		dy;
	double		nx;
	double		ny;
	double		dotp;
	double		x_dist;
	double		y_dist;
	double		x;
	double		y;
	double		px;
	double		py;
	double		thing_ang;
	double		xv;
	double		yv;
	double		thing_ztop;
	double		thing_zlow;
	double		z;
	double		nz;
	t_wall		w;
	t_wall		w2;
	t_thing		monster;
	t_line2f	thing_l;
	double		curr_sect_floor;
	double		new_sect_floor;
	double		curr_sect_ceil;
	double		new_sect_ceil;
	int			sectnum;
	int			clip;
}						t_fillcliplines;

typedef struct			s_raytrace
{
	t_cliplines	*cl;
	double		startx;
	double		starty;
	double		*goalx;
	double		*goaly;
	double		newx;
	double		newy;
	double		vx;
	double		vy;
	double		len;
	int			hitwall;
}						t_raytrace;

# define PF_CROUCH 0x2

typedef struct			s_pvwall
{
	int				flags;
	int				wall_id;
	int				sect_id;
	unsigned short	col0;
	unsigned short	col1;
	double			dist0;
	double			dist1;
	t_line2f		playerspace;
	t_line2f		screenspace;
}						t_pvwall;

# define RF_DEBUG_HUD 0x1
# define DS_OPENING 0x1
# define DS_CLOSING 0x2

typedef struct			s_engine
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	pthread_t		threads[2];
	int				num_walls;
	t_wall			*walls;
	int				num_sectors;
	t_sector		*sectors;
	int				num_things;
	t_thing			*things;
	t_thing			player;
	double			door_bounds[2];
	int				door_state;
	int				doors_opening[2];
	t_v3f			projectile_trajectory[MAX_NUM_PROJECTILES];
	int				projectile_queue_idx;
	int				num_projectiles;
	int				player_flags;
	int				player_pitch_shift;
	double			bullet_damage;
	double			fireball_damage;
	double			sin_ang;
	double			cos_ang;
	double			rev_sin_ang;
	double			rev_cos_ang;
	const uint8_t	*key_states;
	int				num_textures;
	SDL_Surface		**textures;
	int				r_flags;
	int				monster_in_front;
	int				wall_in_front;
	t_pvwall		pvwall_front;
	double			thing_width[TH_END];
	double			thing_height[TH_END];
	int				num_thing_textures;
	SDL_Surface		**thing_textures;
	t_player_items	p_i;
	t_menu			menu;
	char			font_table[128][8];
}						t_engine;

# define PV_CLIPPED0 0x1
# define PV_CLIPPED1 0x2

typedef struct			s_clip
{
	int				*flags;
	unsigned short	*col0;
	unsigned short	*col1;
	double			*dist0;
	double			*dist1;
	t_line2f		*playerspace;
	t_line2f		*screenspace;
}						t_clip;

typedef struct			s_bunch
{
	unsigned short	firstx;
	unsigned short	lastx;
	unsigned short	first_idx;
	unsigned short	last_idx;
}						t_bunch;

typedef struct			s_pvsprite
{
	int				flags;
	int				thing_id;
	unsigned short	col0;
	unsigned short	col1;
	double			dist0;
	double			dist1;
	t_v2f			p;
	t_line2f		playerspace;
	t_line2f		screenspace;
}						t_pvsprite;

# define MAX_YSAVES 348160

enum					e_smost_walltype
{
	SMOSTW_FULL,
	SMOSTW_UP,
	SMOSTW_DOWN,
};

typedef struct			s_clipmost
{
	short					smost[MAX_YSAVES];
	uint16_t				num_smost;
	short					smost_wallstart[MAX_PVWALLS];
	enum e_smost_walltype	smost_walltype[MAX_PVWALLS];
	int32_t					smost_wall[MAX_PVWALLS];
	int						num_smost_walls;
}						t_clipmost;

typedef struct			s_render
{
	t_engine	*eng;
	double		prev_yaw;
	t_pvwall	pvwalls[MAX_PVWALLS];
	int			num_pvwalls;
	t_bunch		bunches[MAX_BUNCHES];
	int			num_bunches;
	t_pvsprite	pvsprites[MAX_PVSPRITES];
	int			num_pvsprites;
	short		umost[WIN_WIDTH];
	short		dmost[WIN_WIDTH];
	t_clipmost	clip;
	int			full_cols;
}						t_render;

typedef struct			s_draw_info
{
	int			first;
	int			last;
	double		top_yl_frac;
	double		top_yh_frac;
	double		mid_frac;
	double		bot_yl_frac;
	double		bot_yh_frac;
	double		top_yl_step;
	double		top_yh_step;
	double		mid_step;
	double		bot_yl_step;
	double		bot_yh_step;
	double		top_height;
	double		bot_height;
	double		s_wall_width;
	double		ceiling_height;
	double		door_height;
	double		floor_height;
	short		upwb[WIN_WIDTH];
	short		tmp_umost[WIN_WIDTH];
	short		dwb[WIN_WIDTH];
	short		tmp_dmost[WIN_WIDTH];
}						t_draw_info;

typedef struct			s_plane_info
{
	double	z;
	int		pitch_shift;
	double	player_x;
	double	player_y;
	double	rev_sin_ang;
	double	rev_cos_ang;
}						t_plane_info;

typedef struct			s_draw_plane
{
	t_plane_info	info;
	t_render		*r;
	t_draw_info		*d;
	SDL_Surface		*texture;
	int				x;
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				twall;
	int				bwall;
	int				lastx[WIN_HEIGHT];
}						t_draw_plane;

typedef struct			s_draw_line
{
	t_render		*r;
	int				x0;
	int				x1;
	int				y;
	SDL_Surface		*texture;
	t_plane_info	*info;
}						t_draw_line;

typedef struct			s_draw_line_local
{
	uint32_t		*dest;
	int				count;
	t_v2f			p0;
	t_v2f			p1;
	double			delta_x;
	double			delta_y;
	double			x0_tex_offset;
	double			y0_tex_offset;
}						t_draw_line_local;

typedef struct			s_plane_thread_info
{
	t_render	*r;
	t_pvwall	*pvwall;
	t_draw_info	*d;
}						t_plane_thread_info;

typedef struct			s_m_monster
{
	int			thing_id;
	double		f_delta;
	t_thing		*monster;
	double		len;
	t_engine	*eng;
	double		xv;
	double		yv;
}						t_m_monster;

typedef struct			s_missile_struct
{
	t_v3f		p;
	t_line2f	w;
	t_v3f		traj;
	double		len;
}						t_missile_struct;

typedef struct			s_bullet_struct
{
	t_v3f		p;
	t_v3f		world;
	t_line2f	w;
}						t_bullet_struct;

typedef struct			s_scansector
{
	t_clip		info;
	int			end_wall;
	int			scansect_idx;
	int			num_scansects;
	int			scansects[MAX_SCANSECTS];
	t_wall		w;
	t_wall		w2;
	t_line2f	l[2];
	double		angle;
	int			new_bunch;
}						t_scansector;

typedef struct			s_viewpace
{
	t_line2f	screenspace;
	double		col0;
	double		col1;
	double		dist0;
	double		dist1;
}						t_viewspace;

typedef struct			s_scanthing
{
	double			x;
	double			y;
	double			px;
	double			py;
	double			thing_ang;
	enum e_thing	type;
	double			xv;
	double			yv;
	int				s;
}						t_scanthing;

typedef struct			s_draw_scene
{
	int		bunch_hits[MAX_BUNCHES];
	int		i;
	int		j;
	int		nearest_bunch;
	int		num_bunches;
	int		w;
}						t_draw_scene;

typedef struct			s_bunch_front
{
	int	b1_firstx;
	int	b1_lastx;
	int	b2_firstx;
	int	b2_lastx;
	int	intersect_idx;
}						t_bunch_front;

typedef struct			s_wall_front
{
	t_line2f	w1;
	t_line2f	w2;
	double		w_vx;
	double		w_vy;
	double		cross_start;
	double		cross_end;
	double		cross_origin;
}						t_wall_front;

typedef struct			s_draw_pvwall
{
	t_pvwall		*pvwall;
	t_draw_info		d;
	t_wall			wall;
	int				is_portal;
	double			scale0;
	double			scale1;
	double			nyceil;
	double			top0_yl;
	double			top1_yl;
	double			top0_yh;
	double			top1_yh;
	double			nyfloor;
	double			bot0_yh;
	double			bot1_yh;
	double			bot0_yl;
	double			bot1_yl;
	double			mid0;
	double			mid1;
	double			yl;
	double			yh;
	int				num;
}						t_draw_pvwall;

typedef struct			s_draw_wall
{
	t_wall		wall;
	SDL_Surface	*m_texture;
	double		wall_len;
	double		wall_height;
	double		m_u0;
	double		m_u1;
	double		m_u_range;
	t_line2f	w;
	double		wp_pl;
	double		m_u0_z0;
	double		m_u1_z1;
	double		f1_z0;
	double		f1_z1;
	double		m_v;
	double		m_vstep;
	double		count;
	int			top_yh;
	int			bot_yl;
	double		alpha;
	double		m_u;
}						t_draw_wall;

typedef struct			s_draw_portal
{
	t_wall		wall;
	SDL_Surface *t_texture;
	SDL_Surface *b_texture;
	double		wall_len;
	double		t_u0;
	double		t_u1;
	double		b_u0;
	double		b_u1;
	double		t_u_range;
	double		b_u_range;
	t_line2f	w;
	double		wp_pl;
	double		t_u0_z0;
	double		t_u1_z1;
	double		b_u0_z0;
	double		b_u1_z1;
	double		f1_z0;
	double		f1_z1;
	double		t_v;
	double		t_vstep;
	double		b_v;
	double		b_vstep;
	double		count;
	int			top_yl;
	int			top_yh;
	int			bot_yl;
	int			bot_yh;
	double		alpha;
	double		t_u;
	double		b_u;
}						t_draw_portal;

typedef struct			s_draw_door
{
	t_wall		wall;
	SDL_Surface	*t_texture;
	SDL_Surface	*m_texture;
	SDL_Surface	*b_texture;
	double		wall_len;
	double		t_u0;
	double		t_u1;
	double		m_u0;
	double		m_u1;
	double		b_u0;
	double		b_u1;
	double		t_u_range;
	double		m_u_range;
	double		b_u_range;
	t_line2f	w;
	double		wp_pl;
	double		t_u0_z0;
	double		t_u1_z1;
	double		m_u0_z0;
	double		m_u1_z1;
	double		b_u0_z0;
	double		b_u1_z1;
	double		f1_z0;
	double		f1_z1;
	double		t_v;
	double		t_vstep;
	double		m_v;
	double		m_vstep;
	double		b_v;
	double		b_vstep;
	double		count;
	double		wall_height;
	int			top_yl;
	int			top_yh;
	int			mid;
	int			bot_yl;
	int			bot_yh;
	double		alpha;
	double		t_u;
	double		m_u;
	double		b_u;
}						t_draw_door;

typedef struct			s_draw_sprite
{
	t_pvsprite		*pvsprite;
	t_thing			thing;
	short			umost[WIN_WIDTH];
	short			dmost[WIN_WIDTH];
	enum e_thing	type;
	short			x0;
	short			x1;
	int				start_x;
	int				end_x;
	int				smost_start;
	SDL_Surface		*texture;
	double			sprite_len;
	double			u0;
	double			u1;
	double			u_range;
	t_line2f		seg;
	double			wp_pl;
	double			u0_z0;
	double			u1_z1;
	double			f1_z0;
	double			f1_z1;
	double			scale0;
	double			scale1;
	double			p_zh;
	double			p_zl;
	double			x0_yl;
	double			x0_yh;
	double			x1_yl;
	double			x1_yh;
	double			thing_screen_width;
	double			yl_step;
	double			yh_step;
	double			yl_frac;
	double			yh_frac;
	double			f_yl;
	double			f_yh;
	double			v;
	double			v_step;
	double			count;
	int				yl;
	int				yh;
	double			alpha;
	double			u;
}						t_draw_sprite;

typedef struct			s_draw_col
{
	int			x;
	short		yl;
	short		yh;
	SDL_Surface *texture;
	int			u;
	double		v;
	double		v_step;
}						t_draw_col;

typedef struct			s_draw_sprites
{
	int	draw_order[MAX_PVSPRITES];
	int	i;
	int	swapped;
	int	tmp;
}						t_draw_sprites;

typedef struct			s_ras
{
	uint32_t	alen;
	int			n_sounds;
	int			i;
	void		*buf;
}						t_ras;

typedef struct			s_gnw
{
	double		tmp;
	double		p_x;
	double		p_y;
	int			hit;
	double		dist;
	int			i;
	t_wall		*w1;
	t_wall		*w2;
}						t_gnw;

typedef struct			s_iow
{
	int		nearest;
	int		match;
	int		sect1;
	int		sect2;
}						t_iow;

typedef struct			s_rat
{
	int			w;
	int			h;
	int			pitch;
	uint8_t		bpp;
	uint32_t	rmask;
	uint32_t	gmask;
	uint32_t	bmask;
	uint32_t	amask;
	int			n_textures;
	int			i;
	void		*pixels;
}						t_rat;

int						sign(double x);
double					cross_product(double x0, double y0, double x1,
		double y1);
void					load_assets(t_engine *eng);
void					sdl_init(t_engine *eng);
void					sdl_init_audio(void);
void					sdl_shutdown(SDL_Window *window);
void					doom_loop(t_engine *eng);
double					add_angle_wrap(double a);
int						pitch_control(int pitch, double delta);
void					update_player(t_engine *engine,
		const uint8_t *key_states, double delta_t);
void					handle_mouse_event(t_engine *eng, const SDL_Event *e);
void					draw_line(SDL_Surface *screen, int x0, int y0, int x1,
		int y1, int color);
int						update_thing_sector(t_engine *engine, t_thing *thing,
		double x, double y);
int						inside_sector(t_engine *eng, double x, double z,
		int num_sector);
int						line_is_out_of_cb(t_clipmove_struct *cm, t_line2f l);
void					fill_walls(t_engine *eng, t_thing *thing,
		t_clipmove_struct *cm, t_fillcliplines *fc);
void					fill_monsters(t_engine *eng, t_thing *thing,
		t_clipmove_struct *cm, t_fillcliplines *fc);
void					fill_cliplines(t_engine *eng, t_thing *thing,
		int sectnum, t_clipmove_struct *cm);
int						clipmove(t_engine *eng, t_thing *thing, t_v3f vec,
		int flags);
int						clipmove_end_func(t_engine *eng, t_thing *thing,
		t_clipmove_struct *cm);
int						pushmove(t_engine *eng, t_thing *thing, int sectnum);
int						bunch_front(const t_render *r, int bunch1, int bunch2);
void					free_assets(t_engine *eng);
void					abort_error(t_engine *eng, char *str, ...);
void					draw_hud(const t_render *r);
void					scansector_things(t_render *r, t_scansector *sc);
void					render(t_engine *eng);
void					draw_scene(t_render *render);
void					draw_sprite(t_render *r, int sprite_id);
void					draw_sprites(t_render *r);
int						viewspace_clip_transform(const t_line2f *l,
		t_clip *info);
void					load_file(t_engine *eng, char *str);
int						get_sector(t_engine *eng, int wall_id);
void					scansector_walls(t_render *r, t_scansector *sc);
int						sprite_wall_front(const t_render *r, int sprite_num,
		int pvwall_num);
double					intersectyx(const t_line2f *l);
double					intersectyminx(const t_line2f *l);
int						viewspace_sub4(t_clip *info, t_viewspace *v);
void					draw_pvwall(t_render *r, int pvwall_id);
void					*draw_floor(void *in);
void					*draw_ceil(void *in);
void					draw_portal_flats(t_render *r, t_pvwall *pvwall,
		t_draw_info *d);
void					draw_wall_flats(t_render *r, t_pvwall *pvwall,
		t_draw_info *d);
void					draw_door_flats(t_render *r, t_pvwall *pvwall,
		t_draw_info *d);
void					dp_handle_wall(t_render *r, int pvwall_id,
		t_draw_pvwall *dp);
void					dp_handle_portal(t_render *r, int pvwall_id,
		t_draw_pvwall *dp);
void					draw_door_flats0(t_render *r, t_pvwall *pvwall,
		t_draw_door *dd);
void					draw_door_flats1(t_draw_info *d, t_pvwall *pvwall,
		t_draw_door *dd);
t_v2f					screen_to_worldspace(int i, int j,
		const t_plane_info *info);
void					draw_hline(t_draw_line dl);
void					init_draw_ceil(t_plane_thread_info **it_ptr,
		t_draw_plane *dp,
		void *in);
int						draw_ceil_loop1(t_plane_thread_info *it,
		t_draw_plane *dp);
void					init_draw_floor(t_plane_thread_info **it_ptr,
		t_draw_plane *dp, void *in);
int						draw_floor_loop1(t_plane_thread_info *it,
		t_draw_plane *dp);
int						clipsprite(t_render *r, int sprite_id,
		t_draw_sprite *ds);
int						clipsprite_most(t_render *r, t_draw_sprite *ds, int i,
		int j);
void					update_pvwall_most(t_render *r, t_draw_pvwall *dp);
int						raytrace(t_clipmove_struct *cm);
char					get_line_intersection(t_line2f l1, t_line2f l2,
		double *p_x, double *p_y);
int						read_alloctextures(int fd, int *num_textures,
		SDL_Surface ***textures);
int						read_allocsounds(int fd, int *num_sounds,
		Mix_Chunk ***ui_sounds);
void					update_doors(t_engine *eng, double f_delta);
void					update_things(t_engine *eng, double f_delta);
void					update_monster(t_engine *eng, int thing_id,
		double f_delta);
void					shoot_bullet(t_engine *eng);
void					launch_missile(t_engine *eng);
void					update_projectile(t_engine *eng, int thing_id,
		double f_delta);
void					init_open_walls(t_engine *eng);
int						player_init_rect(t_engine *eng);
void					blit_player_items(t_engine *eng, t_player_items *p_i,
		int delta, int *pause);
void					init_player_items_var(t_player_items *p_i);
void					player_items_event(t_engine *eng, SDL_Event *e);
void					gun_reload_anim(t_engine *eng);
void					move_gun(t_player_items *p_i,
		const uint8_t *key_states, double delta);
void					move_rpg(t_player_items *p_i,
		const uint8_t *key_states, double delta);
void					move_gun_animation(t_engine *eng,
		const uint8_t *key_states);
void					change_gun(t_engine *eng, t_player_items *p_i,
		int delta);
int						speed_gun_move(t_engine *eng, double delta,
		int img_height);
void					menu(t_engine *eng, t_menu *menu);
void					init_rect(SDL_Rect *rect, int x, int y, int w, int h);
void					update_percent_jp(t_player_items *p_i, int delta);
void					draw_pixel(SDL_Surface *screen, int x, int y,
		int color);
void					screen_mm_coord(t_engine *eng, float *x0, float *y0);
void					player_items_get(t_engine *eng);
void					draw_item_mm(t_engine *eng, float pos_x,
		float pos_y, int item);
void					ui_audio(t_player_items *p_i);
void					player_dammages(t_engine *eng, t_player_items *p_i);
void					game_over(t_engine *eng, t_player_items *p_i,
		double delta);
void					key_hand(t_engine *eng, t_player_items *p_i,
		double delta);
void					display_menu(t_engine *eng, t_player_items *p_i,
		int pause_game);
void					win(t_engine *eng, int *game_pause);
void					display_win(t_engine *eng);
void					gun_display(t_engine *eng, t_player_items *p_i,
		int delta);
void					update_jetpack(t_engine *eng, t_player_items *p_i);
void					update_percent_jp(t_player_items *p_i, int delta);
void					rpg_display_shoot(t_engine *eng, t_player_items *p_i,
		int delta);
void					blit_number(t_engine *eng, int number, int index,
		int typo);
void					update_life(t_player_items *p_i, int delta,
		int *pause);
void					save_item_inv(t_player_items *p_i, int item_type);
void					key_hand_rpg(t_engine *eng, t_player_items *p_i,
		double delta);
void					init_var_menu(t_menu *menu);
int						move_doors(t_engine *eng, int delta, t_menu *menu);
void					cursor_animation(t_menu *menu, t_engine *eng,
		int delta, int delta_inc);
void					menu_audio(int delta, t_engine *eng);
void					init_cursor_rect(t_menu *menu, int led);
void					load_rect_menu(t_menu *menu);
void					keys_event(SDL_Event *event, int *ret, t_engine *eng,
		t_menu *menu);
void					key_shoot(t_engine *eng);
#endif
