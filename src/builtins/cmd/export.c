/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:57:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/31 19:33:18 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);

void export(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	t_llst	*line;
	int		i;
	int		i_color;

	ft_manager_fd(cmd, mini, ast, var);
	if (cmd->m_lst->matrix->size == 1)
	{
		line = mini->m_lst_env->head;
		i = 1;
		i_color = 0;
		while (i <= mini->m_lst_env->size)
		{
			if (i_color > 3)
				i_color = 0;
			ft_putstr_fd(mini->color[i_color], STDOUT_FILENO);
			ft_putlst_fd(line->lst, 1, STDOUT_FILENO);
			ft_putstr_fd(RESET, STDOUT_FILENO);
			i_color++;
			line = line->next;
			i++;
		}
		if (cmd->m_lst->next->type == PIPE)
		{
			close (mini->fd_std[0]);
			close (mini->fd_std[1]);
			free_memory(mini, var, ast, 1);
		}
	}
	else
		ft_putstr_fd("INCLUIR EXPORT\n", 2);
}

static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[1], STDOUT_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
	if (ft_redirect_manager(cmd->m_lst->matrix) < 0)
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
