/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/18 13:30:34 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	ft_execute(t_ast_n *cmd, t_mini *mini, t_ast *ast)
{
	if (cmd == NULL)
		return ;
	ft_execute(cmd->left, mini, ast);
	if (cmd->m_lst->matrix->head->lst->head->c == '(')
		ft_expand_subshell(cmd, mini, ast);
  	else
	{
		ft_execve(cmd, mini, ast);
		if (cmd->m_lst->next->type == PIPE)
			ft_remove_specific_matrix(mini->mmlst, cmd->m_lst->next);
		if (cmd->m_lst->prev->type &( OR_OP | AND_OP))
			ft_remove_specific_matrix(mini->mmlst, cmd->m_lst->prev);
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
	}
}
