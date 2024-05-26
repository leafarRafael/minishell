/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:19:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/26 08:48:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void build_var_and_run_execve(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
static void	ft_valid_command(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);

void	children(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	rl_clear_history();
	expand_wildcard_mlst(cmd->m_lst->matrix);
	ft_expand_m_lst(cmd->m_lst->matrix);
	ft_remove_quote_mlst(cmd->m_lst->matrix);
	ft_manager_fd(cmd, mini, ast, var);
	ft_valid_command(cmd, mini, ast, var);
	build_var_and_run_execve(cmd, mini, ast, var);
}

static void build_var_and_run_execve(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	var->env = path_system_bin(mini->m_lst_env);
	var->command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
	var->path_exe = ft_get_executable(mini, var, ast);
	if (execve(var->path_exe, &var->command_m[0], var->env) < 0)
		perror(var->path_exe);
	free_memory(mini, var, ast, 1);
}

static void	ft_valid_command(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->matrix->size == 1 && cmd->m_lst->matrix->head->lst->size == 0)
	{
		ft_msg_error("''", " command not found");
		free_memory(mini, var, ast, 126);
	}
	if (cmd->m_lst->matrix->size == 0)
		free_memory(mini, var, ast, 0);
}

static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
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
		free_memory(mini, var, ast, 1);
}
