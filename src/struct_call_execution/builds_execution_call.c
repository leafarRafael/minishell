/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builds_execution_call.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:11:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 17:03:15 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builds_execution_call(t_mini *mini)
{
	t_ast	*ast;
	int		index;

	ast = NULL;
	ast = ft_init_ast();
	index = 0;
	while (mini->ast[index] != NULL && index < 40)
		index++;
	mini->ast[index] = ast;
	ft_define_cmd_status(mini->mmlst);
	ft_remove_cmd_status(mini->mmlst);
	command_call_structure(ast, mini->mmlst);
	ft_call_and_exec_manager(ast->root, mini, ast);
}
