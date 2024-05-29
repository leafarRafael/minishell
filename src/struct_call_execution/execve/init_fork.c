/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:39:49 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/29 08:49:24 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*select_function();
void	valid_fork(pid_t *pid, t_ast_n *cmd, int ctrl_func);

void	init_fork(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	void	(*function)(t_ast_n *, t_mini *, t_ast *, t_var_exe *);
	int		ctrl_func;

	expand_wildcard_mlst(cmd->m_lst->matrix);
	ft_expand_m_lst(cmd->m_lst->matrix);
	ft_remove_quote_mlst(cmd->m_lst->matrix);
	ctrl_func = 0;
	ctrl_func = is_builtin(cmd, mini);
	function = select_function(ctrl_func);
	valid_fork(&var->pid, cmd, ctrl_func);
	if (var->pid != -42)
	{
		if (var->pid == 0)
			function(cmd, mini, ast, var);
		else
		{
			parent(cmd, mini, var);
			free_cmd_operator_executed(cmd, mini);
		}	
	}
	else 
		function(cmd, mini, ast, var);
}

void *select_function(int i)
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
	function[_NULL] = NULL;
	return (function[i]);
}

void valid_fork(pid_t *pid, t_ast_n *cmd, int ctrl_func)
{
	if (ctrl_func > 0)
	{
		if (cmd->m_lst->next->type == PIPE || cmd->m_lst->prev->type == PIPE)
		    ((*pid) = fork());
		else
			((*pid) = -42);
	}
	else
		((*pid) = fork());
}
