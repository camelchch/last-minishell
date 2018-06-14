# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 21:06:58 by fsabatie          #+#    #+#              #
#    Updated: 2018/06/14 13:50:45 by saxiao           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Protecting makefile
.PHONY: all clean fclean re

# Defining variables
NAME = minishell

#SRC_PATH = srcs
#INC_PATH = includes

SRC = line_edition.c rm_quoting_in_list.c rm_quoting_in_word.c print.c\
		err_in_words.c is_lexing_type.c command_to_words.c init_add_word.c\
		init_seprator.c for_init_seprator.c here_doc_bse_word.c \
		build_in_1.c\
		main.c sh_table.c update_env.c set_unset_env.c

LIB_NAME = libft.a
PRINTF_NAME = libftprintf.a
LIB_PATH = libft
OBJ = $(SRC:.c=.o)

#SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
#LIB = $(addprefix $(INC_PATH)/,$(LIB_PATH))
LIBFT = $(addprefix $(LIB_PATH)/,$(LIB_NAME))
PRINTF = $(addprefix $(LIB_PATH)/,$(PRINTF_NAME))
#CPPFLAGS = -Wall -Werror -Wextra -ltermcap #-I.
CPPFLAGS = -ltermcap #-I.

# Defining colors

RED = \033[1;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m
BLUE = \033[1;36m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
NC = \033[0m

# Defining rules

all: $(NAME)

$(NAME):
	@echo "${GREEN}Compiling libft." | tr -d '\n'
	@cd $(LIB_PATH) && make re
	@echo " ${GREEN}Done."
	@cd ..
	@echo "${GREEN}Compiling minishell" | tr -d '\n'
	@gcc $(CPPFLAGS) -c $(SRC)
	@gcc $(CPPFLAGS) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo " ${GREEN}Done."

clean:
	@rm -rf $(OBJ)
	@cd $(LIB_PATH) && make clean
	@cd ..

fclean: clean
	@rm -rf $(NAME)
	@cd $(LIB_PATH) && make fclean
	@cd ..

re: fclean all
