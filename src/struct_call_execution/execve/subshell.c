/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:38:49 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 17:50:50 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subshell(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	pid_t	pid_subshell;

	pid_subshell = fork();
	if (pid_subshell == 0)
	{
		init_fork(cmd, mini, var);
		rl_clear_history();
		free_memory(mini, var, g_status_child);
	}
	else
	{
		if (cmd->m_lst->next->type & (AND_OP | OR_OP))
			waitpid(pid_subshell, &mini->status, 2);
		else
			waitpid(-1, &mini->status, 2);
		if (cmd->m_lst->next->type == PIPE)
		{
			dup2(var->tube[0], STDIN_FILENO);
			close(var->tube[0]);
			close(var->tube[1]);
		}
		free_cmd_operator_executed(cmd, mini);
		g_status_child = WEXITSTATUS(mini->status);
	}
}
