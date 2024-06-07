/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:54:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/07 08:56:14 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	status_process_manager(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
static void	file_descriptor_manager(t_ast_n *cmd, t_var_exe *var);

void	parent(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	status_process_manager(cmd, mini, var);
	file_descriptor_manager(cmd, var);
}

static void	status_process_manager(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->next->type & (AND_OP | OR_OP))
		waitpid(var->pid, &mini->status, 0);
	else
		waitpid(-2, &mini->status, 0);
	g_status_child = WEXITSTATUS(mini->status);
}

static void	file_descriptor_manager(t_ast_n *cmd, t_var_exe *var)
{
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[0], STDIN_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
}
