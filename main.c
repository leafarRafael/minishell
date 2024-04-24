/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/24 17:32:25 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	t_var_minishell v;
	char			**env;

	v.looping_shell = 1;
	env = NULL;
	v.temp__environ = __environ;
	v.mrtx_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	v.env = ft_cpy_mtrllst_to_cmtrx(v.mrtx_lst_env);
 	ft_printf_matrix(ft_path_env(v.mrtx_lst_env));
	while (v.looping_shell)
	{
		v.infile = readline("minishell ~:");
		if (!ft_input_is_valid(v.infile))
		{
			__environ = v.env;
			v.input_user = ft_init_lst();
			v.list_matrix = ft_mtrx_mtrx_lst();
			ft_add_string_in_list(v.input_user, v.infile);
			ft_scanner_input(v.input_user);
			while (v.input_user->size > 0)
				ft_create_node_matrix_add_back(v.list_matrix, ft_simple_comand(v.input_user));
			ft_define_cmd_operator(v.list_matrix);
			ft_valid_op_in_subshell(v.list_matrix);
			v.ast = ft_init_ast();
			ft_populetree(v.ast, v.list_matrix);
			ft_printtree(v.ast->root, v.list_matrix);
			ft_free_memory_revert_environ(&v);
		}
	}
	ft_delete_cmatrix(v.env);
	ft_delete_matrix(v.mrtx_lst_env);
}
