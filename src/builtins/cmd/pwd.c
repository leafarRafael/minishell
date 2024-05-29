/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:21:05 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/29 09:18:15 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void putpwd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);

void	pwd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	ft_manager_fd2(cmd, mini, ast, var);
	ft_valid_command2(cmd, mini, ast, var);
	putpwd(cmd, mini, ast, var);
	finished_builtin2(cmd, mini, ast, var);
}

static void putpwd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	t_llst	*node;

	node = mini->m_lst_env->head;
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