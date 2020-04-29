.PHONY: all clean fclean re norme

CC = gcc

FLAGS = -Wall -Wextra -Werror

CPP_FLAGS = -Iinclude

NAME = libftprintf.a

SRC_PATH = ./src
OBJ_PATH = ./obj

SRC_NAME =	ft_printf.c buf.c funnel.c check_1.c check_2.c tools_1.c tools_2.c tools_3.c\
			flag_c.c flag_s.c flag_p.c flag_d.c flag_u_o.c flag_x.c flag_f.c\
			precision.c width.c\

INC_NAME = ft_printf.h

OBJ_NAME = $(SRC_NAME:.c=.o)


SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))


all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(FLAGS) -o $@ -c $<

$(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c
	@mkdir $(OBJLIB_PATH) 2> /dev/null || true
	@$(CC) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf ./obj $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
