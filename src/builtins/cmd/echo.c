/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:20:41 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/03 11:14:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exe_echo(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);

void	echo(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	ft_manager_fd_builtin(cmd, mini, ast, var);
	ft_valid_command_builtin(cmd, mini, ast, var);
	exe_echo(cmd, mini, ast, var);
	finished_builtin(cmd, mini, ast, var);
}

static void exe_echo(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	int		i;

	i = 1;
	ft_remove_lst_front(cmd->m_lst->matrix);
	if (cmd->m_lst->matrix->size == 0)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	if (!ft_strlstcmp(cmd->m_lst->matrix->head->lst, "-n", 2))
	{
		ft_remove_lst_front(cmd->m_lst->matrix);
		i = 0;
	}
	if (cmd->m_lst->matrix->size == 0)
		return ;
	while (cmd->m_lst->matrix->size)
	{
		ft_putlst_fd(cmd->m_lst->matrix->head->lst, i, STDOUT_FILENO);
		ft_remove_lst_front(cmd->m_lst->matrix);
	}
}