/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_and_exec_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/21 10:35:56 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_call_and_exec_manager(t_ast_n *cmd, t_mini *mini, t_ast *ast)
{
	if (cmd == NULL)
		return ;
	ft_call_and_exec_manager(cmd->left, mini, ast);
	if (cmd->m_lst->matrix->head->lst->head->c == '(')
		ft_expand_subshell(cmd, mini, ast);
  	else
		ft_exec_manager(cmd, mini, ast);
}