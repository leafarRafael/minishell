/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_executed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:10:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/09 18:14:26 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_operator_executed(t_ast_n *cmd, t_mini *mini)
{
	if (cmd->m_lst->next->type == PIPE)
	{
		cmd->m_lst->next->next->prev_pipe = 1;
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst->next);
	}
	if (cmd->m_lst->prev->type & (OR_OP | AND_OP))
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst->prev);
	ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
}
