# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:41:47 by rbutzke           #+#    #+#              #
#    Updated: 2024/05/21 14:25:11 by rbutzke          ###   ########.fr        #
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

FILES			:= ./REMOVER_FUNCOES_DEBUG/FUNCOES_TEMPORARIAS.c\
				./REMOVER_FUNCOES_DEBUG/expand_m_lst_to_cmtrx.c

MAIN			:= ./src/minishell.c

REDIRECT		:= ./src/redirect/add_redir_attribute_token/ft_define_command_operator.c\
				./src/redirect/add_redir_attribute_token/ft_remove_command_operator.c\
				./src/redirect/redirect_manager.c\
				./src/redirect/here_doc.c\
				./src/redirect/infile.c\
				./src/redirect/outfile_append.c\
				./src/redirect/outfile_trucate.c\
				./src/redirect/here_doc/here_doc_create_file.c\
				./src/redirect/here_doc/new_lst_heredoc.c\
				./src/redirect/here_doc/write_here_doc.c\
				./src/redirect/ft_open.c

SIMPLE			:=./src/struct_call_execution/call_and_exec_manager.c\
				./src/struct_call_execution/path_executable/get_executable.c\
				./src/struct_call_execution/expanding_parentheses/expand_parentheses.c\
				./src/struct_call_execution/execve/exec_manager.c\
				./src/struct_call_execution/execve/children.c\
				./src/struct_call_execution/execve/parent.c\
				./src/struct_call_execution/command_call_structure.c\
				./src/struct_call_execution/builds_execution_call.c

AS_TREE			:=./src/function_ast/build_tree.c\
				./src/function_ast/init_ast.c\
				./src/function_ast/init_node_ast.c\
				./src/function_ast/delete_tree.c\
				./src/function_ast/add_node_right.c\
				./src/function_ast/add_node_left.c

TOKEN			:= ./src/parse/token/token.c\
				./src/parse/token/token_word.c\
				./src/parse/token/token_operator.c\
				./src/parse/token/token_parentheses.c\
				./src/parse/token/token_after_expandig.c
				
DEL_QUOTES		:= ./src/remove_quotes/remove_quotes_lst.c\
				./src/remove_quotes/remove_quotes_mlst.c

PARSE			:= ./src/parse/scanner/scanner_add_literal_in_all.c\
				./src/parse/scanner/scanner_composite_op.c\
				./src/parse/scanner/scanner_input.c\
				./src/parse/scanner/scanner_parenthes.c\
				./src/parse/scanner/scanner_quotes.c\
				./src/parse/scanner/scanner_simple_op.c\
				./src/parse/scanner/scanner_for_priotity.c\
				./src/parse/scanner/scanner_after_expanding.c

EXPANDER		:= ./src/expanding/expanding.c\
				./src/expanding/expand_mtrx_lst.c\

ERROR			:= ./src/error_and_free_memory/memory_free.c\
				./src/error_and_free_memory/msg_error.c

KEY_WORDS		:= ./src/key_words/add_type_content.c\
				./src/key_words/control_operators.c\
				./src/key_words/dollar_sign.c\
				./src/key_words/is_operator.c\
				./src/key_words/parentheses.c\
				./src/key_words/redirection_ctrl_op.c\
				./src/key_words/string_delimiters.c\
				./src/key_words/words_delimiters.c

PATH_SYSTEM_BIN := ./src/path_system_binaries/path_system_bin.c\

BUILD_IN		:= ./src/build_in/exit.c

SYNTAX_VALID	:= ./src/syntax_validation/valid_input.c\
				./src/syntax_validation/syntax_and_here_doc.c

STDFD			:= ./src/stdfd_manager/swap_tty.c\
				./src/stdfd_manager/close_allfd.c

ENVIRON			:=./src/environ_variable_ctrl/swap_environ.c

SRC				:= $(MAIN) $(FILES) $(AS_TREE) $(PARSE)\
				$(KEY_WORDS) $(SIMPLE) $(REDIRECT)\
				$(ERROR) $(TOKEN) $(DEL_QUOTES)\
				$(EXPANDER) $(PATH_SYSTEM_BIN)\
				$(BUILD_IN) $(SYNTAX_VALID)\
				$(STDFD) $(ENVIRON)

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
	
libft_fclean:
	@$(MAKE) -C $(PATH_MAKE_LIB) fclean --no-print-directory

libft_re:
	@$(MAKE) -C $(PATH_MAKE_LIB) re --no-print-directory

clean:
	@$(CMD_CLEAN) $(NAME)

fclean: clean libft_fclean linked_list_fclean matrix_list_fclean matrix_matrix_list_fclean
	@$(CMD_CLEAN) $(NAME)

re: libft_clean linked_list_clean matrix_list_clean matrix_matrix_list_clean clean all 