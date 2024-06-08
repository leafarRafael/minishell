/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:39:49 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/08 13:47:19 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	*select_function(int i);
static void	valid_fork(pid_t *pid, t_ast_n *cmd, int ctrl_func);
static void	execute(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
static int	ft_valid_command(t_ast_n *cmd);

void	init_fork(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	expand_wildcard_mlst(cmd->m_lst->matrix);
	ft_expand_m_lst(cmd->m_lst->matrix);
	ft_remove_quote_mlst(cmd->m_lst->matrix);
	if (ft_valid_command(cmd))
	{
		free_cmd_operator_executed(cmd, mini);
		return ;
	}
	execute(cmd, mini, var);
}

static void	*select_function(int i)
{
	void	(*function[9]);

	function[_BINARY] = children;
	function[_CD] = cd;
	function[_PWD] = pwd;
	function[_ENV] = env;
	function[_ECHO] = echo;
	function[_EXIT] = my_exit;
	function[_UNSET] = unset;
	function[_EXPORT] = export;
	return (function[i]);
}

static void	valid_fork(pid_t *pid, t_ast_n *cmd, int ctrl_func)
{
	if (ctrl_func > 0)
	{
		if (cmd->m_lst->next->type == PIPE || cmd->m_lst->prev_pipe)
			(*pid) = fork();
		else
			(*pid) = -42;
	}
	else
		(*pid) = fork();
}

static int	ft_valid_command(t_ast_n *cmd)
{
	if (cmd->m_lst->matrix->size == 1
		&& cmd->m_lst->matrix->head->lst->size == 0)
	{
		ft_msg_error("''", " command not found");
		return (1);
	}
	if (cmd->m_lst->matrix->size == 0)
		return (1);
	return (0);
}

static void	execute(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	void	(*function)(t_ast_n *, t_mini *, t_var_exe *);
	int		ctrl_func;

	ctrl_func = 0;
	ctrl_func = is_builtin(cmd);
	function = select_function(ctrl_func);
	valid_fork(&var->pid, cmd, ctrl_func);
	if (var->pid != -42)
		collector_add_back(mini->collect, var->pid);
	if (var->pid != -42)
	{
		if (var->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			rl_clear_history();
			function(cmd, mini, var);
		}
		else
		{
			parent(cmd, mini, var);
			free_cmd_operator_executed(cmd, mini);
		}
	}
	else
		function(cmd, mini, var);
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
