/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/09 20:22:05 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_define_node_tree(t_ast *ast);

int	main(void)
{
	t_mini	mini;
	char	**temp_environ;

	temp_environ = __environ;
	mini.m_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	mini.env = ft_cpy_mtrllst_to_cmtrx(mini.m_lst_env);
	__environ = mini.env;
	while (1)
	{
		printf("\n============================================================================\n");
		mini.input = readline("minishell ~:");
		th_parse_param(mini.input);
		// FREE THE PARSE FOR TEST

		if (!ft_exit(mini.input))
			break ;
		if (!ft_input_is_valid(mini.input))
		{
			__environ = mini.env;
			mini.input_lst = ft_init_lst();
			ft_add_string_in_list(mini.input_lst, mini.input);

			printf("\nREADLINE: \n");
			ft_print_array_lst(mini.input_lst, 0);
			printf("\n");

			ft_scanner_input(mini.input_lst);
			printf("TYPES:\n");
			ft_print_array_lst_content_type(mini.input_lst);

			// ft_parse_and_execute(mini.input_lst, mini.m_lst_env);
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
	if (input->head->type == OPEN_PAREN)
	{
		ft_remove_node_front(input);
		ft_remove_node_back(input);
	}
	new_matrix = ft_mtrx_mtrx_lst();
	while (input->size > 0)
		ft_matrix_add_back(new_matrix,
			ft_simple_comand(input));
	ft_define_cmd_status(new_matrix);
	ft_remove_cmd_status(new_matrix);
	ft_valid_op_in_subshell(new_matrix);
	new_ast = ft_init_ast();
	ft_populetree(new_ast, new_matrix);
	ft_define_node_tree(new_ast);
	ft_execute(new_ast->root, mrtx_lst_env);
	ft_delete_tree(new_ast);
	ft_delete_mtrx_mtrx_lst(new_matrix);
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
	temp = ast->root;
	while (temp != NULL)
	{
		temp->how_to_exe = temp->m_lst->next->type;
		temp = temp->left;
	}
}
