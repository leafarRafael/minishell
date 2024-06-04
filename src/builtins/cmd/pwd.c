/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:21:05 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 07:44:42 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void putpwd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);

void	pwd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, ast, var);
	ft_valid_command_builtin(cmd, mini, ast, var);
	putpwd(cmd, mini, ast, var);
	finished_builtin(cmd, mini, ast, var);
}

static void putpwd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	t_llst	*node;

	node = mini->m_lst_env->head;
	// START AT NEXT??
	while(node->next != mini->m_lst_env->head)
	{
		if (!ft_strlstcmp(node->lst, "PWD=", 4))
		{
			ft_putstr_fd(mini->color[0], STDOUT_FILENO);
			ft_putlst_fd(node->lst, 1, STDOUT_FILENO);
			ft_putstr_fd(RESET, STDOUT_FILENO);
			break ;
		}
		node = node->next;
	}
}
