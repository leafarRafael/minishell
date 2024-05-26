/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/16 16:35:54 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	ft_execute(t_ast_n *cmd, t_mini *mini, t_ast *ast)
{
	if (cmd == NULL)
		return ;
	ft_execute(cmd->left, mini, ast);
	ft_print_matrix_line(cmd->m_lst->matrix);
	if (cmd->m_lst->matrix->head->lst->head->c == '(')
		ft_expand_subshell(cmd, mini, ast);
	// THIS SOULD EXECUTE
		/* else
		ft_execve(cmd, mini, ast); */
}