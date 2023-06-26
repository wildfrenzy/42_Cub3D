# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 01:02:14 by nmaliare          #+#    #+#              #
#    Updated: 2023/05/23 13:40:40 by bmacmaho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -g3 -fsanitize=address
#-Werror

NAME = cub3d

HEADER = cub3d.h parsing/parsing.h

SRC = main.c draw.c utils.c inits.c controls.c exit.c 2d.c raycast.c raycast_utils.c screen.c textures.c \
	parsing/additional_utils.c parsing/freedom.c parsing/get_next_line.c parsing/get_next_line_utils.c \
	parsing/map_creator.c parsing/parse.c parsing/parse_colours.c parsing/parse_map.c parsing/parse_textures.c

OBJ = $(SRC:.c=.o)

# Libft
#LIBFT =  $(LIBFT_DIR)libft.a
#LIBFT_DIR = ./inc/libft/
#LIBFT_FLAGS =  -lft -L $(LIBFT_DIR)

# MLX $(MLX)
MLX =  ./MLX42/build/libmlx42.a
MLX_DIR = ./MLX42/include/
MLX_FLAGS = -I$(MLX_DIR) -ldl -lglfw -pthread -lm

#HEADER_FLAGS = -I $(LIBFT_DIR)

# COLORS
NOC         = \033[0m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@cc $(FLAGS) $(OBJ) -o $(NAME) $(MLX) $(MLX_FLAGS)
	@printf "$(GREEN)$(NAME) successfully compiled !$(NOC)\n"

$(OBJ): %.o:%.c #$(HEADER)
	@cc $(FLAGS) -c $< -o $@ #$(HEADER_FLAGS)
	@printf "$(GREEN)[\342\234\205] $(notdir $@)\n";

#$(LIBFT):
#	@printf "$(BLUE)Compiling libft files: $(NOC)"
#	@make -sC $(LIBFT_DIR)
#	@printf "$(GREEN)[\342\234\205]\n"

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
#@make fclean -sC $(LIBFT_DIR)

re: fclean all

exec: all clean
	./$(NAME) ./parsing/0.cub

.PHONY:	all clean fclean re