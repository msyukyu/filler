# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/05 17:21:38 by dabeloos          #+#    #+#              #
#    Updated: 2019/03/05 17:45:49 by dabeloos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fillerminator

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

PRINTFHEAD	= ./libft/ft_printf/includes

CHEAD		= ./libft

CTHISHEAD	= ./includes

MAIN_F		= main.o

PARSING_F	= decode_input.o \
			  decode_player.o \
			  read.o

O_FILES		= $(addprefix ./main/, $(MAIN_F)) \
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

re:			fclean all

.PHONY: clean fclean all re