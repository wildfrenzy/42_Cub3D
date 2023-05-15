# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 01:02:14 by nmaliare          #+#    #+#              #
#    Updated: 2023/05/15 13:48:00 by barramacmah      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra
#-Werror

NAME = cube3d

#HEADER =

SRC = main.c draw.c

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

$(NAME): $(OBJ) #$(HEADER)
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

exec: all
	make clean
	./$(NAME)

.PHONY:	all clean fclean re