# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:41:47 by rbutzke           #+#    #+#              #
#    Updated: 2024/03/29 10:45:59 by rbutzke          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= minishell
CFLAGS			:= -Wextra -Wall -Werror
CC				:= cc
LIBFT			:= ./lib/lib_get_print/libft.a
PATH_MAKE_LIB	:= ./lib/lib_get_print

FILES			:= ./main.c FUNCOES_TEMPORARIAS.c

ARRAY_LIST		:= ./src/function_list/init_list.c\
				./src/function_list/create_node_add_back_lst.c\
				./src/function_list/create_node_add_front_lst.c\
				./src/function_list/remove_node_front.c\
				./src/function_list/remove_node_back.c\
				./src/function_list/remove_specific_node.c\
				./src/function_list/remove_specific_content.c\
				./src/function_list/delete_list.c\
				./src/function_list/add_node_back.c\
				./src/function_list/add_node_front.c\
				./src/function_list/create_string_list.c\
				./src/function_list/remove_and_return_node.c

MATRIX_LIST		:= ./src/matrix_lst/init_matriz.c\
				./src/matrix_lst/init_line_lst.c\
				./src/matrix_lst/add_line_front.c\
				./src/matrix_lst/add_line_back.c

PARSE			:= ./src/parse/scanner_array_list.c\
				./src/parse/ask_to_operador.c

KEY_WORDS		:= ./src/key_words/key_words.c ./src/key_words/is_operator.c

SRC				:= $(FILES) $(ARRAY_LIST) $(PARSE) $(KEY_WORDS) $(MATRIX_LIST)

INCLUDE			:= -I ./include -I ./lib/lib_get_print/includes
CMD_CLEAN		:= rm -Rf
CMD_FCLEAN		:= rm -rf

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)

$(NAME):
	@$(CC) $(SRC) $(LIBFT) $(INCLUDE) -o $(NAME) -g3 -lreadline

$(LIBFT): libft

libft:
	@$(MAKE) -C $(PATH_MAKE_LIB) --no-print-directory

libft_clean:
	@$(MAKE) -C $(PATH_MAKE_LIB) fclean --no-print-directory

libft_re:
	@$(MAKE) -C $(PATH_MAKE_LIB) re --no-print-directory

clean:
	@$(CMD_CLEAN) $(NAME)

fclean: clean libft_clean
	@$(CMD_CLEAN) $(NAME)

re: clean, fclean, libft_re, pipex_re, $(LIBFT)