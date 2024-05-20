/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:54:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/20 10:57:06 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	status_process_manager(t_ast_n *cmd, t_var_exe *var);
static void	file_descriptor_manager(t_ast_n *cmd, t_var_exe *var);


void parent(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	status_process_manager(cmd, var);
	file_descriptor_manager(cmd, var);
}

static void	status_process_manager(t_ast_n *cmd, t_var_exe *var)
{
	if (cmd->m_lst->next->type & (AND_OP | OR_OP))
		waitpid(var->pid, &status_child, 2);
	else
		waitpid(-1, &status_child, 2);
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


