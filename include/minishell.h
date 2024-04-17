/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:48:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/17 12:50:40 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "ft_printf.h"
# include "libft.h"
# include "string.h"
# include "key_words.h"
# include "array_lst.h"
# include "matrix_lst.h"
# include "matrix_matrix_lst.h"
# include "get_next_line.h"
# include "expanding.h"
# include "parser.h"
# include "scanner.h"
# include "token.h"
# include "abstract_syntax_tree.h"

typedef struct s_variables_minishell
{
	char			*infile;
	char			**temp__environ;
	char			**env;
	int 			i;
	int				looping_shell;
	t_lst			*input_user;
	t_mtrx_lst		*matrix_lst;
	t_mtrx_lst		*mrtx_lst_env;
	t_mtrx_mtrx		*list_matrix;
	t_ast			*ast;
}			t_var_minishell;

/*
			Function parse
*/
void		ft_scanner_input(t_lst *lst);
int			ft_have_operator(t_lst *lst);
void		ft_scanner_input(t_lst *lst);
int			ft_delete_cmatrix(char **matrix);
int			ft_define_cmd_operator(t_mtrx_mtrx *m_m_lst);
void		ft_populetree(t_ast *tree, t_mtrx_mtrx *mtrx_mtrx);



void	ft_printf_matrix(char **matrix);
void	ft_print_array_lst(t_lst *lst, int front_back);
void	ft_print_array_lst_content_type(t_lst *lst);
void	show_str_type(int type);
void	print_all_type();
void	print_operator(t_lst *lst);
void	ft_print_matrix_line(t_mtrx_lst *m_line);
int		ft_separate_operators(t_mtrx_lst	*matrix_lst, t_lst *input_user);
void	ft_print_lst_matrix(t_mtrx_mtrx *m_l);
void	ft_print_todos_os_tokens_expandidos(t_mtrx_mtrx *mtrx_mtrx);
void	ft_printtree(t_ast_node *root, t_mtrx_mtrx *mtrx_mtrx);


#endif