/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:52:21 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 17:52:03 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_variables(t_var_exe *var);
static int	operator_manager(t_ast_n *cmd, t_mini *mini, t_var_exe *var);

void	ft_exec_manager(t_ast_n *cmd, t_mini *mini)
{
	t_var_exe	var;

	init_variables(&var);
	if (operator_manager(cmd, mini, &var))
		return ;
	if (cmd->m_lst->in_parent)
		subshell(cmd, mini, &var);
	else
		init_fork(cmd, mini, &var);
}

static int	operator_manager(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd == NULL)
		return (1);
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return (1);
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return (1);
	if (cmd->m_lst->next->type == PIPE)
	{
		if (pipe(var->tube) < 0)
		{
			ft_msg_error("pipe error", strerror(errno));
			free_memory(mini, var, g_status_child + 1);
		}
		return (0);
	}
	return (0);
}

void	free_cmd_operator_executed(t_ast_n *cmd, t_mini *mini)
{
	if (cmd->m_lst->next->type == PIPE)
	{
		cmd->m_lst->next->next->prev_pipe = 1;
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst->next);
	}
	if (cmd->m_lst->prev->type & (OR_OP | AND_OP))
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst->prev);
	ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
}

static void	init_variables(t_var_exe *var)
{
	var->path_exe = NULL;
	var->env = NULL;
	var->command_m = NULL;
}
