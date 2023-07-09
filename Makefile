# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 01:02:14 by nmaliare          #+#    #+#              #
#    Updated: 2023/07/08 15:55:49 by bmacmaho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
# -g3 -fsanitize=address

NAME = cub3D

HEADER = cub3d.h parsing/parsing.h

SRC = main.c errors.c raycast.c raycast_utils.c draw.c utils.c inits.c controls.c exit.c textures.c \
	parsing/additional_utils.c parsing/freedom.c parsing/get_next_line.c parsing/get_next_line_utils.c \
	parsing/map_creator.c parsing/parse.c parsing/parse_colours.c parsing/parse_map.c parsing/parse_textures.c

OBJ = $(SRC:.c=.o)

# Libft
LIBFT =  $(LIBFT_DIR)libft.a
LIBFT_DIR = ./Libft/
LIBFT_FLAGS =  -lft -L $(LIBFT_DIR)

# MLX $(MLX)
MLX =  ./MLX42/build/libmlx42.a
MLX_DIR = ./MLX42/include/

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
MLX_FLAGS = -I$(MLX_DIR) -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
else
MLX_FLAGS = -I$(MLX_DIR) -ldl -lglfw -pthread -lm
endif

# COLORS
NOC         = \033[0m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	@cc $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(MLX) $(MLX_FLAGS)
	@printf "$(GREEN)$(NAME) successfully compiled !$(NOC)\n"

$(OBJ): %.o:%.c
	@cc -g3 -c $< -o $@
	@printf "$(GREEN)[\342\234\205] $(notdir $@)\n";

$(LIBFT):
	@printf "$(BLUE)Compiling libft files: $(NOC)"
	@make -sC $(LIBFT_DIR)
	@printf "$(GREEN)[\342\234\205]\n"

clean:
	@if [ "$(wildcard $(addprefix ./, $(OBJ)))" ]; then\
		printf "$(BLUE)Cleaning $(NAME) files: $(YELLOW)$(OBJ)$(NOC) $(GREEN) [ \342\234\205 ] $(NOC)\n";\
		/bin/rm -f $(OBJ);\
	else\
		printf "$(YELLOW)There's no object files in $(NAME) \360\237\230\261$(NOC)\n";\
	fi

fclean: clean
	@if [ "$(wildcard $(addprefix ./, $(NAME)))" ]; then\
		printf "$(BLUE)Cleaning $(NAME): $(YELLOW)$(NAME) $(GREEN) [ \342\234\205 ]\n$(NOC)";\
		/bin/rm -f $(NAME);\
	else\
		printf "$(YELLOW)There's no $(GREEN)$(NAME) $(YELLOW)file here \360\237\230\261\n$(NOC)";\
	fi
	@make fclean -sC $(LIBFT_DIR)

re: fclean all

exec: all clean
	./$(NAME) ./maps/0.cub

val: all clean
	valgrind ./$(NAME) ./maps/0.cub

.PHONY:	all clean fclean re exec val