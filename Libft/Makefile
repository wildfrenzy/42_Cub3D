# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 15:53:14 by nmaliare          #+#    #+#              #
#    Updated: 2022/12/11 19:12:00 by nmaliare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =  -Wall -Wextra -Werror
NAME = libft.a
HEADER = libft.h

SRC = ft_bzero.c ft_isdigit.c ft_memset.c ft_strlcpy.c ft_strrchr.c \
	ft_isalnum.c ft_isprint.c ft_strchr.c ft_strlen.c ft_tolower.c \
	ft_isalpha.c ft_memcpy.c ft_strdup.c ft_strncmp.c ft_toupper.c \
	ft_atoi.c ft_isascii.c ft_memmove.c ft_strlcat.c ft_strnstr.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c\
	ft_putendl_fd.c ft_substr.c ft_memcmp.c ft_memchr.c ft_split.c \
	ft_strjoin.c ft_calloc.c ft_itoa.c ft_strtrim.c\

BONUS_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

# COLORS
NOC         = \033[0m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJ) $(HEADER)
	@printf "$(GREEN)Libft successfully compiled !$(NOC)\n"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ): %.o:%.c
	@cc $(FLAGS) -c $< -o $@
	@printf "$(GREEN)[\342\234\205] $(notdir $@)\n";

bonus:$(BONUS_OBJ) $(HEADER)
	@printf "$(GREEN)Libft bonus part successfully compiled !$(NOC)\n"
	@ar rc $(NAME) $(BONUS_OBJ)
	@ranlib $(NAME)

$(BONUS_OBJ): %.o:%.c
	@cc $(FLAGS) -c $< -o $@
	@printf "$(GREEN)[\342\234\205] $(notdir $@)\n";

clean:
	@if [ "$(wildcard $(addprefix ./, $(OBJ)))" ]; then\
		printf "$(BLUE)Cleaning libft files: $(YELLOW)$(OBJ)$(NOC) $(GREEN) [ \342\234\205 ] $(NOC)\n";\
		/bin/rm -f $(OBJ);\
	else\
		printf "$(YELLOW)There's no object files in libft \360\237\230\261$(NOC)\n";\
	fi
	@if [ "$(wildcard $(addprefix ./, $(BONUS_OBJ)))" ]; then\
    		printf "$(BLUE)Cleaning bonus libft files: $(YELLOW)$(BONUS_OBJ) $(GREEN) [ \342\234\205 ] $(NOC)\n";\
    		/bin/rm -f $(BONUS_OBJ);\
    	else\
    		printf "$(YELLOW)There's no bonus object files in libft \360\237\230\261$(NOC)\n";\
    	fi
fclean: clean
	@if [ "$(wildcard $(addprefix ./, $(NAME)))" ]; then\
		printf "$(BLUE)Cleaning libft.a: $(YELLOW)$(NAME) $(GREEN) [ \342\234\205 ]\n$(NOC)";\
		/bin/rm -f $(NAME);\
	else\
		printf "$(YELLOW)There's no $(GREEN)libft.a $(YELLOW)file here \360\237\230\261\n$(NOC)";\
	fi
re: fclean all

.PHONY:	all clean fclean re bonus
