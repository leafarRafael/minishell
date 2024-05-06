/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/06 10:08:21 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_define_node_tree(t_ast *ast);

int	main(void)
{
	t_mini	mini;
	char	**temp_environ;
	t_lst	*new_lst;

	temp_environ = __environ;
	mini.m_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	mini.env = ft_cpy_mtrllst_to_cmtrx(mini.m_lst_env);
	__environ = mini.env;
	while (1)
	{
		mini.input = readline("minishell ~:");
		if (!ft_exit(mini.input))
			break ;
		if (!ft_input_is_valid(mini.input))
		{
			__environ = mini.env;
			mini.input_lst = ft_init_lst();
			ft_add_string_in_list(mini.input_lst, mini.input);
			ft_scanner_input(mini.input_lst);
			new_lst = ft_duplst(mini.input_lst, ft_cpynode, ft_add_node_back);
			mini.fd_std[0] = dup(STDIN_FILENO);
			mini.fd_std[1] = dup(STDOUT_FILENO);
			ft_parse_and_execute(mini.input_lst, mini.m_lst_env);
			dup2(mini.fd_std[0], STDIN_FILENO);
			dup2(mini.fd_std[1], STDOUT_FILENO);
			close(mini.fd_std[0]);
			close(mini.fd_std[1]);
			if (mini.input_lst)
				free(mini.input_lst);
			__environ = temp_environ;
		}
	}
	ft_delete_cmatrix(mini.env);
	ft_delete_matrix(mini.m_lst_env);
}

void	ft_parse_and_execute(t_lst *input, t_mtrx_lst *mrtx_lst_env)
{
	t_ast		*new_ast;
	t_mtrx_mtrx	*new_matrix;

	if (input->size == 0)
		return ;
	new_matrix = ft_mtrx_mtrx_lst();
	while (input->size > 0)
		ft_matrix_add_back(new_matrix,
			ft_simple_comand(input));
	ft_define_cmd_status(new_matrix);
	ft_remove_cmd_status(new_matrix);
	new_ast = ft_init_ast();
	ft_populetree(new_ast, new_matrix);
	ft_execute(new_ast->root, mrtx_lst_env);
	ft_delete_tree(new_ast);
	ft_delete_mtrx_mtrx_lst(new_matrix);
}

void	ft_parse_and_execute2(t_lst *input, t_mtrx_lst *mrtx_lst_env, int op)
{
	t_ast		*new_ast;
	t_mtrx_mtrx	*new_matrix;

	if (input->size == 0)
		return ;
	if (input->head->type == OPEN_PAREN)
	{
		ft_remove_node_front(input);
		ft_remove_node_back(input);
	}
	if (is_operator(op))
		ft_create_node_add_back(input, '|');
	ft_scanner_input(input);
	new_matrix = ft_mtrx_mtrx_lst();
	while (input->size > 0)
		ft_matrix_add_back(new_matrix,
			ft_simple_comand(input));
	ft_define_cmd_status(new_matrix);
	ft_remove_cmd_status(new_matrix);
	new_ast = ft_init_ast();
	ft_populetree(new_ast, new_matrix);
	ft_execute(new_ast->root, mrtx_lst_env);
	ft_delete_tree(new_ast);
	ft_delete_mtrx_mtrx_lst(new_matrix);
}
