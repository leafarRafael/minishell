/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:54:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/13 15:35:14 by rbutzke          ###   ########.fr       */
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
	{
		waitpid(var->pid, &mini->status, 0);
		if (WIFSIGNALED(mini->status))
		{
			if (WTERMSIG(mini->status) == SIGQUIT)
			{
				ft_putstr_fd("Quit (core dumped)\n", 2);
				g_status_child = 128 + WTERMSIG(mini->status);
			}
			else if (WTERMSIG(mini->status) == SIGINT)
				g_status_child = 0;
		}
		else
			g_status_child = WEXITSTATUS(mini->status);
	}
	if (cmd->m_lst->next->type & (AND_OP | OR_OP))
		swap_tty(RESTORE, mini);
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
