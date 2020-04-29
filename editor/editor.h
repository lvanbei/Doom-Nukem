/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:20:59 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/05 13:08:17 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "common.h"

# define UGL2BIS UI_GUN_LOAD_2_BIS
# define UGS1 UI_GUN_SHOOT_1
# define UGS2 UI_GUN_SHOOT_2
# define GRID_WIDTH 800
# define GRID_HEIGHT GRID_WIDTH
# define MENU_WIDTH 300
# define WIN_WIDTH 1100
# define WIN_HEIGHT GRID_HEIGHT
# define MAX_FILENAME_LEN 100
# define MAX_WIDTH 50
# define MIN_WIDTH 8
# define MAX_SELECT_WALLS 5
# define NUM_TEXTURES 7
# define ARROWK_DELTA 10

typedef struct			s_view
{
	double	xmin;
	double	ymin;
	double	w;
	double	dx;
	double	dx_1;
}						t_view;

enum					e_tool
{
	TL_NONE = -1,
	TL_WALL = 0,
	TL_THING,
	TL_SELECT_WALL,
	TL_SELECT_SECTOR,
	TL_SELECT_THING,
	TL_END,
};

enum					e_mb
{
	LMB = 0,
	RMB,
	END_MB,
};

typedef struct			s_istates
{
	uint8_t			space_nav;
	uint8_t			mb_down[END_MB];
	uint8_t			shift_down;
	int				mouse_x;
	int				mouse_y;
	enum e_tool		hot_tool;
	enum e_tool		active_tool;
	int				active_wall_has_co;
	int				active_wall;
	int				hot_wall;
	enum e_thing	th_hot;
	enum e_thing	th_active;
	int				active_thing;
	int				txp_hot_texture;
	int				active_sector;
	int				hot_sector;
	int				active_slider;
	double			tl_thing_default_yaw;
}						t_istates;

enum					e_texpick
{
	TXP_NONE = -1,
	TXP_BOT = 0,
	TXP_MAIN,
	TXP_TOP,
	TXP_FLOOR,
	TXP_CEIL,
	TXP_END,
};

typedef struct			s_tl_wall
{
	int		num_walls;
	int8_t	active_tex_pick;
	int8_t	hot_tex_pick;
	double	default_floor_height;
	double	default_ceiling_height;
	int8_t	default_floor_texture;
	int8_t	default_ceiling_texture;
	int8_t	default_b_texture;
	int8_t	default_m_texture;
	int8_t	default_t_texture;
}						t_tl_wall;

typedef struct			s_wall_inter
{
	int			i;
	t_line2f	w;
	t_line2f	w2;
	double		min_0;
	double		max_0;
	double		min_1;
	double		max_1;
}						t_wall_inter;

typedef struct			s_draw_portal
{
	t_line2f	w;
	double		nx;
	double		ny;
	double		dx;
	double		dy;
	double		len;
	t_line2f	arrow;
	double		ang;
	double		ang0;
	double		p0_x;
	double		p0_y;
	double		ang1;
	double		p1_x;
	double		p1_y;
}						t_draw_portal;

typedef struct			s_mask
{
	int		alpha;
	int		r;
	int		g;
	int		b;
}						t_mask;

enum					e_ui_textures
{
	UI_PLAYER = 0,
	UI_HEAL,
	UI_AMMO,
	UI_MONSTER,
	UI_KEYCARD,
	UI_JETPACK_FUEL,
	UI_RPG,
	UI_MOUSE_ENDING,
	UI_DEADMONSTER,
	UI_FIREBALL,
	UI_IMPACT,
	UI_END,
};

enum					e_ui_element
{
	UIE_NONE = -1,
	UIE_TEXTURE_PICKER = 0,
	UIE_VARIABLE_CONTROL,
	UIE_BUTTON,
	UIE_THING_PICK,
};

# define SLIDER_SENSITIVITY 10.0f
# define MAX_UI_ELEMENTS 6
# define MAX_VAR_CONTROLS 6
# define MAX_BUTTONS 6
# define MIN_FLOOR_HEIGHT 0.0f
# define MAX_CEIL_HEIGHT 16.0f

typedef struct			s_context_menu
{
	enum e_ui_element	ui_elements[MAX_UI_ELEMENTS];
	int8_t				*tex_pick_p[TXP_END];
	double				*var_control[MAX_VAR_CONTROLS];
	double				var_control_clamp[MAX_VAR_CONTROLS][2];
	char				var_control_strs[MAX_VAR_CONTROLS][15];
	SDL_Rect			var_control_bounds[MAX_VAR_CONTROLS];
	int8_t				num_var_controls;
	void				(*button_action[MAX_BUTTONS])(void *);
	char				button_strs[MAX_BUTTONS][15];
	SDL_Rect			button_bounds[MAX_BUTTONS];
}						t_context_menu;

typedef struct			s_ed
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	t_istates		istates;
	t_tl_wall		tl_w;
	char			tool_name[TL_END][15];
	SDL_Rect		tool_textbounds[TL_END];
	SDL_Rect		thing_typebounds[TH_VISIBLE_END];
	SDL_Rect		tex_pick_strsbounds[TXP_END];
	char			tex_pick_strs[TXP_END][15];
	SDL_Rect		texture_pickbounds[NUM_TEXTURES + 1];
	t_context_menu	context_menu[TL_END];
	t_wall			*tl_selected_walls[MAX_SELECT_WALLS];
	t_view			view;
	char			filename[MAX_FILENAME_LEN];
	int				num_walls;
	t_wall			walls[MAX_WALLS];
	int				num_sectors;
	t_sector		sectors[MAX_SECTORS];
	int				num_things;
	t_thing			things[MAX_THINGS];
	unsigned char	player_set;
	t_thing			player;
	SDL_Surface		*textures[NUM_TEXTURES];
	SDL_Surface		*ed_textures[UI_END];
	SDL_Surface		*menu_surfaces[MENU_SURFACE_END];
	SDL_Surface		*player_ui_surfaces[UI_SURFACES_END];
	Mix_Chunk		*ui_sound[UI_SOUND_END];
	double			thing_height[TH_VISIBLE_END];
	char			font_table[128][8];
}						t_ed;

typedef struct			s_wall_update_c
{
	int		i;
	uint8_t	wall_status[MAX_WALLS];
	int		wall2;
	int		sect1;
	int		sect2;
	double	max_height;
}						t_wall_update_c;

typedef struct			s_delete_sector
{
	int	start_wall;
	int	num_walls;
	int	i;
	int	p_x;
	int	p_y;
	int	parent_co_start_wall;
	int	cur0;
	int	cur1;
	int	nw;
	int	parent_sect;
}						t_delete_sector;

typedef struct			s_sect_clock
{
	int	i;
	int	p_idx;
	int	curr_x;
	int	curr_y;
	int	end_wall;
	int	next_wall_idx;
	int	prev_wall_idx;
}						t_sect_clock;

typedef struct			s_tl_wallf
{
	double	p_x;
	double	p_y;
	int		parent_sector;
	int		last_wall_idx;
	int		stored_clockwise;
	int		end_wall;
	int		match;
	int		w2_sect;
	int		o_end_of_parent_sect;
	int		i;
	t_wall	*parent_sect_end;
	t_wall	*new_sect;
}						t_tl_wallf;

typedef struct			s_tl_select_wall
{
	double		tmp;
	double		dist;
	double		p_x;
	double		p_y;
	t_wall		*w1;
	t_wall		*w2;
	int			hit;
	int			down;
}						t_tl_select_wall;

typedef struct			s_box
{
	double	xmin;
	double	ymin;
	double	xmax;
	double	ymax;
}						t_box;

typedef struct			s_drawl
{
	double	error_adj;
	double	error_acc;
	int		delta_x;
	int		delta_y;
	int		tmp;
	int		xdir;
	int		error_acctmp;
}						t_drawl;

typedef struct			s_line_inter
{
	double	s1_x;
	double	s1_y;
	double	s2_x;
	double	s2_y;
	double	s;
	double	t;
}						t_line_inter;

typedef struct			s_draw_rect
{
	uint32_t	*dest;
	int			x0;
	int			x1;
	int			y0;
	int			y1;
	int			len;
}						t_draw_rect;

typedef struct			s_draw_thing
{
	double		fx;
	double		fy;
	int			x;
	int			y;
	double		w;
	double		h;
	double		ratio;
	double		scale;
	t_thing		player;
	SDL_Rect	rect;
	int			i;
}						t_draw_thing;

void					init_ed0(t_ed *ed);
void					init_ed1(t_ed *ed);
void					init_ed2(t_ed *ed);
void					init_ed3(t_ed *ed);
void					init_ed4(t_ed *ed);
void					init_ed5(t_ed *ed);
void					init_ed6(t_ed *ed);
void					init_ed7(t_ed *ed);
void					init_ed8(t_ed *ed);
void					load_assets(t_ed *ed);
void					load_assets0(t_ed *ed);
void					load_assets1(t_ed *ed);
void					load_assets2(t_ed *ed);
void					load_assets3(t_ed *ed);
void					load_assets4(t_ed *ed);
void					load_assets5(t_ed *ed);
void					check_assets(t_ed *ed);
void					init_alpha_filter_surface(SDL_Surface *src, t_mask m);
void					wall_update_checks(t_ed *ed);
void					thing_update_checks(t_ed *ed);
int						safety_checks(t_ed *ed);
void					load_file(t_ed *ed);
void					save_file(t_ed *ed);
void					core_loop(t_ed *ed);
void					sdl_init(t_ed *ed);
void					sdl_shutdown(SDL_Window *window);
void					delete_sector(t_ed *ed, int sect_id);
void					render(t_ed *ed);
void					draw_line(SDL_Surface *screen, t_line2 d,
		int color);
void					menu_interactions(t_ed *ed, SDL_Event *e);
void					free_assets(t_ed *ed);
void					abort_error(t_ed *ed, char *str, ...);
void					draw_grid(SDL_Surface *surface, const t_view *view);
void					handle_key(t_ed *ed, SDL_KeyboardEvent *e);
void					handle_scroll(t_ed *ed, SDL_MouseWheelEvent *e);
void					handle_mouse(t_ed *ed, SDL_Event *e);
void					map_to_screen(const t_view *view, t_v2f p, double *x,
		double *y);
void					screen_to_map(t_view *view, t_v2 p, double *dest_x,
		double *dest_y);
void					screen_to_map_round(t_view *view, t_v2 p,
		double *dest_x, double *dest_y);
int						was_released(t_istates *istates, SDL_Event *e,
		enum e_mb mb);
int						was_pressed(t_istates *istates, SDL_Event *e,
		enum e_mb mb);
void					draw_menu(t_ed *ed);
int						append_wall(t_ed *ed, int x, int y, int next_wall);
void					set_link_next(t_ed *ed, int start_wall, int end_wall);
void					set_link_prev(t_ed *ed, int start_wall, int end_wall);
int						sector_is_clockwise(t_ed *ed, int num_sector);
int						point_in_rect(int x, int y, const SDL_Rect *rect);
void					tl_wall(t_ed *ed, int x, int y);
int						tl_wall5(t_ed *ed, t_tl_wallf *tw);
void					tl_thing(t_ed *ed, int screen_x, int screen_y);
void					tl_select_wall(t_ed *ed, int screen_x, int screen_y,
		int down);
void					tl_select_sector(t_ed *ed, int screen_x, int screen_y,
		int down);
void					tl_select_thing(t_ed *ed, int screen_x, int screen_y);
int						get_sector(t_ed *ed, int wall_id);
void					update_wall_selectors(t_ed *ed, int start_wall,
		int num_walls);
void					release_walls(t_ed *ed, int screen_x, int screen_y);
void					gather_walls(t_ed *ed, int screen_x, int screen_y);
int						inside_sector(t_ed *ed, double x, double y,
		int num_sector);
int						get_parent_sector(t_ed *ed, double x, double y);
int						wall_intersects(t_ed *ed, int wall_id, int num_walls);
double					dist2(double x0, double y0, double x1, double y1);
void					delete_active_thing(void *a);
void					delete_thing(t_ed *ed, int thing_id);
int						get_co_wall(t_ed *ed, int idx_w);
void					toggle_portal(t_ed *ed, int wall_id);
void					toggle_portal_active_wall(void *a);
void					delete_active_sector(void *a);
void					set_link_prev(t_ed *ed, int start_wall, int end_wall);
void					tool_switch(t_ed *ed, SDL_Event *e);
void					texture_picker_click2(t_ed *ed, SDL_Event *e,
		t_context_menu *m);
void					texture_picker_click(t_ed *ed, SDL_Event *e,
		t_context_menu *m);
void					draw_line2_clipped(t_ed *ed, t_line2f l, int color);
void					intersections(t_line2f *l, t_box b);
void					draw_line5(SDL_Surface *screen, t_line2 *l,
		t_drawl *d, int color);
void					draw_pixel(SDL_Surface *screen, int x, int y,
		int color);
char					line_intersection(t_line2f l1, t_line2f l2,
		double *p_x, double *p_y);
void					draw_wall(t_ed *ed, int i, int color);
void					draw_portal_arrow(t_ed *ed, int i, int color);
void					draw_walls(t_ed *ed);
int						point_in_view(const t_view *view, double x, double y);
void					draw_thing(t_ed *ed, t_draw_thing *dt, double size);
int						write_player(int fd, const t_thing *player);
int						write_sectors(int fd, uint32_t num_sectors,
		const t_sector sectors[MAX_SECTORS]);
int						write_walls(int fd, uint32_t num_walls,
		const t_wall walls[MAX_WALLS]);
int						write_code(int fd);
int						write_things(int fd, uint32_t num_things,
		const t_thing things[MAX_THINGS]);
void					draw_things(t_ed *ed);
void					draw_tl_w(t_ed *ed);
void					draw_menu_tool(t_ed *ed);
void					draw_rect(SDL_Surface *surface, const SDL_Rect *rect,
		int color);
void					draw_thing_types(t_ed *ed);
void					draw_thing_types(t_ed *ed);

#endif
