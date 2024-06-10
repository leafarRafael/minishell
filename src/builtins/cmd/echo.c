/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:20:41 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 10:47:53 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	exe_echo(t_ast_n *cmd);
static void	put_echo(int flag, t_mlst *mlst);

void	echo(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
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
	exe_echo(cmd);
	finished_builtin(cmd, mini, var);
}

static void	exe_echo(t_ast_n *cmd)
{
	t_builtin	v;

	v.flag = 1;
	ft_remove_lst_front(cmd->m_lst->matrix);
	if (cmd->m_lst->matrix->size == 0)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	if (cmd->m_lst->matrix->size == 1
		&& cmd->m_lst->matrix->head->lst->size == 0)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	if (!ft_strlstcmp(cmd->m_lst->matrix->head->lst, "-n"))
	{
		ft_remove_lst_front(cmd->m_lst->matrix);
		v.flag = 0;
	}
	put_echo(v.flag, cmd->m_lst->matrix);
}

static void	put_echo(int flag, t_mlst *mlst)
{
	if (mlst->size == 0)
		return ;
	while (mlst->size)
	{
		ft_putlst_fd(mlst->head->lst, 0, STDOUT_FILENO);
		ft_remove_lst_front(mlst);
		if (mlst->size)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
