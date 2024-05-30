/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:38:49 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/30 15:12:15 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subshell(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	pid_t	pid_subshell;

	pid_subshell = fork();
	if (pid_subshell == 0)
	{
		init_fork(cmd, mini, ast, var);
		free_memory(mini, var, ast, status_child);
	}
	else
	{
		if (cmd->m_lst->next->type & (AND_OP | OR_OP))
			waitpid(pid_subshell, &status_child, 2);
		else
			waitpid(-1, &status_child, 2);
		if (cmd->m_lst->next->type == PIPE)
		{
			dup2(var->tube[0], STDIN_FILENO);
			close(var->tube[0]);
			close(var->tube[1]);
		}
		free_cmd_operator_executed(cmd, mini);
	}
}