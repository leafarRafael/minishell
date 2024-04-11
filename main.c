/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/11 18:35:28 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	t_var_minishell v;
	char			**matrix;

	v.input_user = ft_init_lst();
	v.list_matrix = ft_mtrx_mtrx_lst();
	v.infile = readline("minishell ~:");
	ft_add_string_in_list(v.input_user, v.infile);
	ft_scanner_input(v.input_user);
	while (v.input_user->size > 0)
		ft_create_node_matrix_add_back(v.list_matrix, ft_simple_comand(v.input_user));
	ft_define_cmd_operator(v.list_matrix);
	matrix = ft_cpy_mtrllst_to_cmtrx(v.list_matrix->head->matrix);
	ft_printf_matrix(matrix);
	//ft_print_lst_matrix(v.list_matrix);

	v.ast = ft_init_ast();
	ft_build_tree(v.ast, v.list_matrix->head->matrix, 10);

	ft_delete_mtrx_mtrx_lst(v.list_matrix);
	ft_delete_cmatrix(matrix);
	free(v.input_user);
	free(v.infile);
}
