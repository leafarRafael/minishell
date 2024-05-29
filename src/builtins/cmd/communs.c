/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:00:31 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/29 10:01:07 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_manager_fd2(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[1], STDOUT_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
	if (ft_redirect_manager(cmd->m_lst->matrix) < 0)
		free_memory(mini, var, ast, 1);
}

void	ft_valid_command2(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->matrix->size == 1 && cmd->m_lst->matrix->head->lst->size == 0)
	{
		ft_msg_error("''", " command not found");
		//free_memory(mini, var, ast, 126);
	}
	if (cmd->m_lst->matrix->size == 0)
		return ;
		//free_memory(mini, var, ast, 0);
}

void	finished_builtin2(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->next->type == PIPE || cmd->m_lst->prev->type == PIPE)
	{
		close (mini->fd_std[0]);
		close (mini->fd_std[1]);
		status_child = 0;
		free_memory(mini, var, ast, status_child);
	}
}