/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_and_exec_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 18:09:56 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_call_and_exec_manager(t_ast_n *cmd, t_mini *mini)
{
	if (cmd == NULL)
		return ;
	ft_call_and_exec_manager(cmd->left, mini);
	if (cmd->m_lst->matrix->head->lst->head->c == '(')
		ft_expand_subshell(cmd, mini);
	else
		ft_exec_manager(cmd, mini);
}
