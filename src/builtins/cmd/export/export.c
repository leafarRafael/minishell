/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:57:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 15:32:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	export(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	if (ft_manager_fd_builtin(cmd, mini, var))
	{
		ft_status_builtin(mini, 1, __ERROR);
		return ;
	}
	ft_valid_command_builtin(cmd);
	ft_status_builtin(mini, 0, INIT_SUCCESS);
	mini->collect->last->status = 0;
	if (cmd->m_lst->matrix->size == 1)
		export_putenv(mini);
	else
		export_addvar(cmd, mini);
	finished_builtin(cmd, mini, var);
}
