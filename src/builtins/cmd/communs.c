/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:00:31 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:23:44 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_manager_fd_builtin(t_ast_n *cmd,
				t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[1], STDOUT_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
	if (ft_redirect_manager(cmd->m_lst->matrix) < 0)
		free_memory(mini, var, status_child);
}

void	ft_valid_command_builtin(t_ast_n *cmd,
				t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->matrix->size == 1
		&& cmd->m_lst->matrix->head->lst->size == 0)
		ft_msg_error("''", " command not found");
	if (cmd->m_lst->matrix->size == 0)
		return ;
}

void	finished_builtin(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->next->type == PIPE || cmd->m_lst->prev_pipe)
	{
		rl_clear_history();
		free_memory(mini, var, status_child);
	}
}
