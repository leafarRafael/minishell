/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builds_execution_call.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:11:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/30 15:21:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builds_execution_call(t_lst *input, t_mini *mini)
{
	t_ast		*ast;

	ast = NULL;
	ast = ft_init_ast();
	ft_define_cmd_status(mini->mmlst);
	ft_remove_cmd_status(mini->mmlst);
	command_call_structure(ast, mini->mmlst);
	ft_call_and_exec_manager(ast->root, mini, ast);
	ft_delete_tree(ast);
}
