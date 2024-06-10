/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_and_exec_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 08:15:26 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_variables(t_var_exe *var);
static int	operator_manager(t_ast_n *cmd, t_mini *mini, t_var_exe *var);

void	ft_call_and_exec_manager(t_ast_n *cmd, t_mini *mini)
{
	t_var_exe	var;

	if (cmd == NULL)
		return ;
	ft_call_and_exec_manager(cmd->left, mini);
	if (cmd->m_lst->matrix->head->lst->head->c == '(')
		ft_expand_subshell(cmd, mini);
	else
	{
		init_variables(&var);
		if (operator_manager(cmd, mini, &var))
			return ;
		setup_command(cmd, mini, &var);
	}
}

static void	init_variables(t_var_exe *var)
{
	var->path_exe = NULL;
	var->env = NULL;
	var->command_m = NULL;
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
