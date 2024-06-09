/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:02:06 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/09 18:49:34 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include "builtins.h"

static void	*select_function(int i);
static void	valid_fork(pid_t *pid, t_ast_n *cmd, int ctrl_func);

void	execute(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	void	(*function)(t_ast_n *, t_mini *, t_var_exe *);
	int		ctrl_func;

	ctrl_func = 0;
	ctrl_func = is_builtin(cmd);
	function = select_function(ctrl_func);
	valid_fork(&var->pid, cmd, ctrl_func);
	collector_add_back(mini->collect, &var->pid, node_collect_pid);
	if (var->pid != -42)
	{
		if (var->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
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

static void	*select_function(int i)
{
	void	(*function[9]);

	function[_BINARY] = binary;
	function[_CD] = cd;
	function[_PWD] = pwd;
	function[_ENV] = env;
	function[_ECHO] = echo;
	function[_EXIT] = my_exit;
	function[_UNSET] = unset;
	function[_EXPORT] = export;
	return (function[i]);
}
