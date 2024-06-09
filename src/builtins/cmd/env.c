/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:20:08 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/09 11:39:52 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	ft_execute_env(t_mini *mini);

void	env(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, var);
	ft_valid_command_builtin(cmd);
	ft_status_builtin(mini, 0, INIT_SUCCESS);
	ft_execute_env(mini);
	finished_builtin(cmd, mini, var);
}

static void	ft_execute_env(t_mini *mini)
{
	t_builtin	v;

	v.line = mini->m_lst_env->head;
	v.i_color = 1;
	v.index = 1;
	while (v.index <= mini->m_lst_env->size)
	{
		if (v.i_color > 3)
			v.i_color = 1;
		ft_putstr_fd(mini->color[v.i_color], STDOUT_FILENO);
		ft_putlst_fd(v.line->lst, 1, STDOUT_FILENO);
		ft_putstr_fd(RESET, STDOUT_FILENO);
		v.line = v.line->next;
		v.i_color++;
		v.index++;
	}
}
