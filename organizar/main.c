/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/02 10:20:39 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_define_node_tree(t_ast *ast);

int	main(void)
{
	t_var_minishell	v;
	char			**env;

	v.looping_shell = 1;
	env = NULL;
	v.temp__environ = __environ;
	v.mrtx_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	v.env = ft_cpy_mtrllst_to_cmtrx(v.mrtx_lst_env);
	while (v.looping_shell)
	{
		v.infile = readline("minishell ~:");
		if (!ft_exit(v.infile))
			break ;
		if (!ft_input_is_valid(v.infile))
		{
			__environ = v.env;
			v.input_user = ft_init_lst();
			v.list_matrix = ft_mtrx_mtrx_lst();
			ft_add_string_in_list(v.input_user, v.infile);
			ft_scanner_input(v.input_user);
			while (v.input_user->size > 0)
				ft_matrix_add_back(v.list_matrix,
					ft_simple_comand(v.input_user));
			ft_define_cmd_status(v.list_matrix);
			ft_remove_cmd_status(v.list_matrix);
			ft_valid_op_in_subshell(v.list_matrix);
			v.ast = ft_init_ast();
			ft_populetree(v.ast, v.list_matrix);
			ft_execute(&v, v.ast->root, v.mrtx_lst_env);
			ft_free_memory_revert_environ(&v);
		}
	}
	ft_delete_cmatrix(v.env);
	ft_delete_matrix(v.mrtx_lst_env);
}
/* 
void	ft_parse_and_execute(t_var_minishell *v, t_lst *input)
{
	t_var_minishell	mini;

	if (input->size == 0)
		return ;
	if (!v)
		return ;
	if (input->head->type == OPEN_PAREN)
	{
		ft_remove_node_front(input);
		ft_remove_node_back(input);
	}
	mini.list_matrix = ft_mtrx_mtrx_lst();
	while (input->size > 0)
		ft_matrix_add_back(mini.list_matrix,
			ft_simple_comand(input));
	ft_define_cmd_status(mini.list_matrix);
	ft_remove_cmd_status(mini.list_matrix);
	ft_valid_op_in_subshell(mini.list_matrix);
	mini.ast = ft_init_ast();
	ft_populetree(mini.ast, mini.list_matrix);
	ft_define_node_tree(mini.ast);
	ft_execute(v, mini.ast->root, v->mrtx_lst_env);
	ft_free_memory_revert_environ(&mini);
	ft_free_memory_revert_environ(v);
	ft_delete_cmatrix(v->env);
	ft_delete_matrix(v->mrtx_lst_env);
}

void	ft_define_node_tree(t_ast *ast)
{
	t_ast_node	*temp;

	temp = ast->root;
	while (temp != NULL)
	{
		temp->type = temp->m_lst->matrix->head->lst->head->type;
		temp = temp->left;
	}
} */