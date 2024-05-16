/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/16 14:47:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	ft_execute(t_ast_n *cmd, t_mini *mini, t_ast *ast)
{
	if (cmd == NULL)
		return ;
	ft_execute(cmd->left, mini, ast);
	/* ft_print_matrix_line(cmd->m_lst->matrix); */
	if (cmd->m_lst->matrix->head->lst->head->c == '(')
		ft_expand_subshell(cmd, mini, ast);
	else
		ft_execve(cmd, mini, ast);
}
