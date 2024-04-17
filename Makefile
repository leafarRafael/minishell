# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:41:47 by rbutzke           #+#    #+#              #
#    Updated: 2024/04/17 15:19:25 by rbutzke          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= minishell
CFLAGS			:= -Wextra -Wall -Werror
CC				:= cc
LIBFT			:= ./lib/lib_get_print/libft.a
PATH_MAKE_LIB	:= ./lib/lib_get_print

LINKED_LIST		:= ./lib/lib_list/lib_list.a
MAKE_LINKED_L	:= ./lib/lib_list/circular_linked_list

MATRIX_LIST		:= ./lib/lib_list/lib_list.a
MAKE_MATRIX_L	:= ./lib/lib_list/circular_matrix_list

MTRX_MTRX_L		:= ./lib/lib_list/lib_list.a
MAKE_MTRX_MTRX	:= ./lib/lib_list/circular_matrix_matrix_list

FILES			:= ./main.c FUNCOES_TEMPORARIAS.c delete_cmatrix.c define_ast.c

AS_TREE			:=./src/function_ast/build_tree.c\
				./src/function_ast/init_ast.c\
				./src/function_ast/init_node_ast.c\
				./src/function_ast/delete_tree.c\
				./src/function_ast/add_node_right.c\
				./src/function_ast/add_node_left.c

PARSE			:= ./src/parse/scanner/scanner_add_literal_in_all.c\
				./src/parse/scanner/scanner_composite_op.c\
				./src/parse/scanner/scanner_input.c\
				./src/parse/scanner/scanner_parenthes.c\
				./src/parse/scanner/scanner_quotes.c\
				./src/parse/scanner/scanner_simple_op.c\
				./src/parse/scanner/scanner_for_priotity.c\
				./src/parse/ask_to_operador.c\
				./src/parse/popule_matrix_list.c\
				./src/parse/expanding/expanding.c\
				./src/parse/expanding/expand_m_lst_to_cmtrx.c\
				./src/parse/token/token.c\
				./src/parse/ft_define_command_operator.c

KEY_WORDS		:= ./src/key_words/add_type_content.c\
				./src/key_words/control_operators.c\
				./src/key_words/dollar_sign.c\
				./src/key_words/is_operator.c\
				./src/key_words/parentheses.c\
				./src/key_words/redirection_ctrl_op.c\
				./src/key_words/string_delimiters.c\
				./src/key_words/words_delimiters.c

SRC				:= $(FILES) $(AS_TREE) $(PARSE) $(KEY_WORDS)

INCLUDE			:= -I ./include\
				-I lib/lib_get_print/includes\
				-I lib/lib_list/circular_linked_list/include\
				-I lib/lib_list/circular_matrix_list/include\
				-I lib/lib_list/circular_matrix_matrix_list/include

CMD_CLEAN		:= rm -Rf
CMD_FCLEAN		:= rm -rf

all: $(NAME)

$(NAME): $(SRC) $(LIBFT) $(LINKED_LIST) $(MATRIX_LIST) $(MTRX_MTRX_L)

$(NAME):
	@$(CC) $(SRC) $(LIBFT) $(LINKED_LIST) $(INCLUDE) -o $(NAME) -g3 -lreadline

$(LIBFT): libft

$(LINKED_LIST): linked_list

$(MATRIX_LIST): matrix_list

$(MTRX_MTRX_L): matrix_matrix_list

linked_list:
	@$(MAKE) -C $(MAKE_LINKED_L) --no-print-directory

linked_list_clean:
	@$(MAKE) -C $(MAKE_LINKED_L) clean --no-print-directory

linked_list_fclean:
	@$(MAKE) -C $(MAKE_LINKED_L) fclean --no-print-directory

linked_list_re:
	@$(MAKE) -C $(MAKE_LINKED_L) re --no-print-directory

matrix_list:
	@$(MAKE) -C $(MAKE_MATRIX_L) --no-print-directory

matrix_list_clean:
	@$(MAKE) -C $(MAKE_MATRIX_L) clean --no-print-directory

matrix_list_fclean:
	@$(MAKE) -C $(MAKE_MATRIX_L) fclean --no-print-directory

matrix_list_re:
	@$(MAKE) -C $(MAKE_MATRIX_L) re --no-print-directory

matrix_matrix_list:
	@$(MAKE) -C $(MAKE_MTRX_MTRX) --no-print-directory

matrix_matrix_list_clean:
	@$(MAKE) -C $(MAKE_MTRX_MTRX) clean --no-print-directory

matrix_matrix_list_fclean:
	@$(MAKE) -C $(MAKE_MTRX_MTRX) fclean --no-print-directory

matrix_matrix_list_re:
	@$(MAKE) -C $(MAKE_MTRX_MTRX) re --no-print-directory

libft:
	@$(MAKE) -C $(PATH_MAKE_LIB) --no-print-directory

libft_clean:
	@$(MAKE) -C $(PATH_MAKE_LIB) clean --no-print-directory

libft_re:
	@$(MAKE) -C $(PATH_MAKE_LIB) re --no-print-directory

clean:
	@$(CMD_CLEAN) $(NAME)

fclean: clean libft_clean linked_list_fclean matrix_list_fclean matrix_matrix_list_fclean
	@$(CMD_CLEAN) $(NAME)

re: libft_clean linked_list_clean matrix_list_clean matrix_matrix_list_clean clean all 