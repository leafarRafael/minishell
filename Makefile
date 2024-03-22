# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:41:47 by rbutzke           #+#    #+#              #
#    Updated: 2024/03/22 14:44:32 by rbutzke          ###   ########.fr        #
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
				./src/array_lst/delete_list.c

INCLUDE			:= -I ./include -I ./lib/lib_get_print/includes
CMD_CLEAN		:= rm -Rf
CMD_FCLEAN		:= rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(FILES)

$(NAME):
	@$(CC) $(FILES) $(ARRAY_LIST) $(LIBFT) $(INCLUDE) -o $(NAME) -lreadline

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