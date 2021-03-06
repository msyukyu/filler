# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/05 17:21:38 by dabeloos          #+#    #+#              #
#    Updated: 2019/03/21 18:17:40 by dabeloos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# -g -fsanitize=address
# -Wno-unused-function

NAME		= dabeloos.filler

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -O3

PRINTFHEAD	= ./libft/ft_printf/includes

CHEAD		= ./libft

THISHEAD	= ./includes

MAIN_F		= main.o \
			  utils.o \
			  rng_v.o \
			  rng_h.o \
			  rng_b.o \
			  rng_s.o \
			  position_finder.o \
			  position_iterator.o \
			  pc_place_cond_support.o \
			  pc_place_condition.o \
			  sonar_support.o \
			  sonar.o \
			  distance_scorer.o \
			  enemy_on_sight.o \
			  enemy_eater.o \
			  player.o

PARSING_F	= utils.o \
			  freer.o \
			  are_support.o \
			  are_creator.o \
			  map_decoder.o \
			  map_creator.o \
			  piece_decoder.o \
			  piece_cropper.o \
			  dimensions_decoder.o \
			  turn_decoder.o \
			  player_decoder.o
			  
READ_F		= str_realloc_join.o \
			  remain_editor.o \
			  reader.o

O_FILES		= $(addprefix ./main/, $(MAIN_F)) \
			  $(addprefix ./read/, $(READ_F)) \
			  $(addprefix ./parsing/, $(PARSING_F))

END_E		= \033[00m
RED_E		= \033[01;31m
GREEN_E		= \033[01;32m
YELLOW_E	= \033[01;33m
PURPLE_E	= \033[01;35m
CYAN_E		= \033[01;36m
WHITE_E		= \033[01;37m
BOLD_E		= \033[1m
UNDERLINE_E	= \033[4m

$(NAME):	$(O_FILES)
			@make -C libft/
			@gcc -o $(NAME) $(O_FILES) -L./libft/ -lft
			@echo "$(GREEN_E)end compilation$(END_E)"

all:		$(NAME)

%.o:		%.c
			@$(CC) $(CFLAGS) -c -o $@ $< -I$(CHEAD) -I$(PRINTFHEAD) \
			-I$(THISHEAD)

clean:
			@rm -f $(O_FILES)
			@make -C libft/ clean
			@echo "$(PURPLE_E)end clean$(END_E)"

fclean:		clean
			@rm -f $(NAME)
			@make -C libft/ fclean
			@echo "$(RED_E)end fclean$(END_E)"

re:			fclean all

.PHONY: clean fclean all re