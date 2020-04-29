# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/28 16:39:15 by hde-moff          #+#    #+#              #
#    Updated: 2020/03/01 19:33:15 by hde-moff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem
E_NAME = vis_ed


#game-engine
FILES = main sdl core_loop update_player exit \
		c_mouse inside_sector \
		clipmove  clipmove2 pushmove raytrace \
		clipmove_fillcliplines clipmove_fillcliplines_monster \
		clipmove_fillcliplines_walls \
		load_file load_file2 util math \
		r_main r_scansector_viewspace r_scansector_viewspace2 \
		r_scansector_things r_scansector_walls \
		r_draw_scene r_draw_pvwall r_draw_pvwall2 \
		r_draw_wall_flats r_draw_wall_floor_ceil r_draw_wall_floor_ceil2 \
		r_draw_wall_floor_ceil3 r_draw_wall_floor_ceil4 r_draw_portal_flats \
		r_draw_door_flats r_draw_door_flats2 r_vis r_hud \
		r_sprites r_draw_sprite r_clipsprite r_clipsprite2 \
		p_things p_monster p_ballistic p_ballistic2 p_door \
		player_init_rect player_core_loop_items player_items_event player_init \
		menu player_items_get player_move_rpg player_move_gun \
		player_change_gun player_audio player_dammages player_jet_pack \
		player_gun player_rpg player_display_number player_update_life \
		player_save_items player_key_hand_2 player_win menu_2 menu_3\
	  	game_over player_key_hand menu_pause toggle_door key_shoot

#editor
E_FILES = main load_file save_file core_loop sdl r_main r_grid line \
	  c_keys c_mouse r_menu exit load_assets load_assets2 \
	  tl_wall tl_wall2 tl_wall_util util2 tl_select_wall tl_thing \
	  tl_select_sector \
	  tl_select_sector2 tl_select_thing tl_select_wall2 mouse_util mouse_menu \
	  util init_ed init_ed2 safe_guard safe_guard2 mouse_menu2 \
	  draw_line draw_line_intersections line2 save_file2 r_main2 r_main3 \
	  r_menu2

#common
C_FILES = r_font read_file math math2 slow_std
		

SRC = $(addprefix engine/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix engine/obj/, $(addsuffix .o, $(FILES)))
C_SRC = $(addprefix common/, $(addsuffix .c, $(C_FILES)))
C_OBJ = $(addprefix common/obj/, $(addsuffix .o, $(C_FILES)))
E_SRC = $(addprefix editor/, $(addsuffix .c, $(E_FILES)))
E_OBJ = $(addprefix editor/obj/, $(addsuffix .o, $(E_FILES)))
COMMON_DEPS = common/common.h common/ft_printf/ft_printf.h
ENGINE_DEPS = engine/engine.h $(COMMON_DEPS)
EDITOR_DEPS = editor/editor.h $(COMMON_DEPS)

CURRENT_DIR := $(subst Makefile,,$(abspath $(lastword $(MAKEFILE_LIST))))

SDL_DIR=$(CURRENT_DIR)SDL2
SDL_BUILD=$(SDL_DIR)/build
SDL_BIN=$(SDL_DIR)/bin
SDL_CONFIG=$(SDL_BIN)/bin/sdl2-config

SDL_MIX_DIR=$(CURRENT_DIR)SDL2_mixer
SDL_MIX_BUILD=$(SDL_MIX_DIR)/build

CFLAGS = -I common -Wall -Wextra -O3 `$(SDL_CONFIG) --cflags`
LDFLAGS = -lpthread `$(SDL_CONFIG) --static-libs` common/ft_printf/libftprintf.a $(SDL_BIN)/lib/libSDL2_mixer.a 

all: $(NAME) $(E_NAME)

$(NAME):$(OBJ) $(C_OBJ)
	gcc $(OBJ) $(C_OBJ) $(PRINTF_OBJ) -o $(NAME) $(LDFLAGS)

$(E_NAME):$(E_OBJ) $(C_OBJ)
	gcc $(E_OBJ) $(C_OBJ) -o $(E_NAME) $(LDFLAGS)

clean:
	make -C common/ft_printf/ clean
	rm -rf $(OBJ)
	rm -rf $(DEPS)
	rm -rf $(E_OBJ)
	rm -rf $(C_OBJ)

fclean: clean
	make -C common/ft_printf/ fclean
	rm -rf $(NAME)
	rm -rf $(E_NAME)
	
re: fclean all

engine/obj/%.o: engine/%.c $(ENGINE_DEPS)
	@mkdir -p engine/obj
	gcc -o $@ -c $< $(CFLAGS)

editor/obj/%.o: editor/%.c $(EDITOR_DEPS)
	@mkdir -p editor/obj
	gcc -o $@ -c $< $(CFLAGS)

common/obj/%.o: common/%.c $(COMMON_DEPS)
	make -C common/ft_printf/
	@mkdir -p common/obj
	gcc -o $@ -c $< $(CFLAGS)

sdl:
	cd $(SDL_BUILD); CC="sh $(SDL_DIR)build-scripts/gcc-fat.sh" && ../configure --disable-shared --prefix=$(SDL_BIN) && make -j && make install
	cd $(SDL_MIX_DIR); CC="sh $(SDL_DIR)build-scripts/gcc-fat.sh" && ./configure --disable-shared --prefix=$(SDL_BIN) && make -j && make install

sdl_clean:
	cd $(SDL_BUILD); make clean ; make uninstall
	cd $(SDL_MIX_DIR); make clean ; make uninstall

.PHONY: all clean fclean re
