/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:19:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 16:54:22 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bld_var_and_run_execve(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
static void	ft_valid_command(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
static void	ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_var_exe *var);

void	children(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	rl_clear_history();
	ft_manager_fd(cmd, mini, var);
	ft_valid_command(cmd, mini, var);
	bld_var_and_run_execve(cmd, mini, var);
}

static void	bld_var_and_run_execve(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	var->env = path_system_bin(mini->m_lst_env);
	var->command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
	var->path_exe = ft_get_executable(mini, var);
	if (execve(var->path_exe, &var->command_m[0], __environ) < 0)
		perror(var->path_exe);
	free_memory(mini, var, 1);
}

static void	ft_valid_command(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->matrix->size == 1
		&& cmd->m_lst->matrix->head->lst->size == 0)
	{
		ft_msg_error("''", " command not found");
		free_memory(mini, var, 126);
	}
	if (cmd->m_lst->matrix->size == 0)
		free_memory(mini, var, 0);
}

static void	ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	close (mini->fd_std[0]);
	close (mini->fd_std[1]);
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[1], STDOUT_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
	if (ft_redirect_manager(cmd->m_lst->matrix) < 0)
		free_memory(mini, var, 1);
}
