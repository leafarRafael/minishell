/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:20:41 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/05 17:38:05 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	exe_echo(t_ast_n *cmd);

void	echo(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, var);
	ft_valid_command_builtin(cmd);
	exe_echo(cmd);
	g_status_child = 0;
	finished_builtin(cmd, mini, var);
}

static void	exe_echo(t_ast_n *cmd)
{
	int		i;
	int		index;
	t_llst	*lnode;

	i = 1;
	ft_remove_lst_front(cmd->m_lst->matrix);
	if (cmd->m_lst->matrix->size == 0)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	if (cmd->m_lst->matrix->size == 1 && cmd->m_lst->matrix->head->lst->size == 0)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	if (!ft_strlstcmp(cmd->m_lst->matrix->head->lst, "-n"))
	{
		ft_remove_lst_front(cmd->m_lst->matrix);
		i = 0;
	}
	if (cmd->m_lst->matrix->size == 0)
		return ;
	index = 0;
	lnode = cmd->m_lst->matrix->head;
	while (index < cmd->m_lst->matrix->size)
	{
		ft_putlst_fd(lnode->lst, i, STDOUT_FILENO);
		index++;
		lnode = lnode->next;
	}
}
