# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:41:47 by rbutzke           #+#    #+#              #
#    Updated: 2024/03/24 13:13:52 by rbutzke          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= minishell
CFLAGS			:= -Wextra -Wall -Werror
CC				:= cc
LIBFT			:= ./lib/lib_get_print/libft.a
PATH_MAKE_LIB	:= ./lib/lib_get_print
FILES			:= ./main.c FUNCOES_TEMPORARIAS.c

ARRAY_LIST		:= ./src/array_lst/init_array_list.c\
				./src/array_lst/creat_addnode_back_array_list.c\
				./src/array_lst/creat_addnode_front_array_list.c\
				./src/array_lst/remove_node_front.c\
				./src/array_lst/remove_node_back.c\
				./src/array_lst/remove_specific_node.c\
				./src/array_lst/remove_specific_content.c\
				./src/array_lst/delete_list.c\
				./src/array_lst/add_node_back.c\
				./src/array_lst/add_node_front.c\
				./src/array_lst/create_matrix_array_lst.c

PARSE			:= ./src/parse/scanner_array_list.c

KEY_WORDS		:= ./src/key_words/key_words.c

INCLUDE			:= -I ./include -I ./lib/lib_get_print/includes
CMD_CLEAN		:= rm -Rf
CMD_FCLEAN		:= rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(FILES)

$(NAME):
	@$(CC) $(FILES) $(ARRAY_LIST) $(PARSE) $(KEY_WORDS) $(LIBFT) $(INCLUDE) -o $(NAME) -g3 -lreadline

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