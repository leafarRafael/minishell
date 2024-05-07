/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 15:02:28 by rbutzke          ###   ########.fr       */
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
			free(mini.input);
			ft_scanner_input(mini.input_lst);
			mini.fd_std[0] = dup(STDIN_FILENO);
			mini.fd_std[1] = dup(STDOUT_FILENO);
			mini.mmlst = init_mmlst();
			mini.ast = ft_init_ast();
				while (mini.input_lst->size > 0)
			ft_mmlst_add_back(mini.mmlst, ft_token_cmd(mini.input_lst));
			ft_define_cmd_status(mini.mmlst);
			ft_remove_cmd_status(mini.mmlst);
			ft_populetree_left(mini.ast, mini.mmlst);
			ft_parse_exe(mini.input_lst, mini.m_lst_env, &mini, mini.ast->root);
			ft_delete_mmlst(mini.mmlst);
			ft_delete_tree(mini.ast);
			dup2(mini.fd_std[0], STDIN_FILENO);
			dup2(mini.fd_std[1], STDOUT_FILENO);
			close(mini.fd_std[0]);
			close(mini.fd_std[1]);
			__environ = temp_environ;
		}
	}
	ft_delete_cmatrix(mini.env);
	ft_delete_matrix(mini.m_lst_env);
}

void	ft_parse_exe(t_lst *input, t_mlst *mlst_env, t_mini *mini, t_ast_n *ast_n)
{
	t_ast_n	*node;
	t_ast_n	*temp;

	while (input->size > 0)
		ft_mmlst_add_back(mini->mmlst, ft_token_cmd(input));
	if (input)
	{
		free(input);
		input = NULL;
	}
	ft_define_cmd_status(mini->mmlst);
	ft_remove_cmd_status(mini->mmlst);
	ft_populetree_left(mini->ast, mini->mmlst);
	if (ast_n == mini->ast->root)
	{
		if (!ast_n->m_lst)
		{
			temp = ast_n->left;
			free(ast_n);
			mini->ast->root = temp;
		}
	}
	if (!ast_n->m_lst)
	{
		node = mini->ast->root;
		while (node->left != NULL)
		{
			if (node->left == ast_n)
			{
				temp = ast_n->left;
				free(ast_n);
				mini->ast->size--;
				node->left = temp;	
				ast_n = node;;
				break ;
			}
			node = node->left;
		}
	}
	ft_execute(ast_n, mlst_env, mini);
}
