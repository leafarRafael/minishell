/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:39:49 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 10:58:15 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	ft_valid_command(t_ast_n *cmd, t_mini *mini);

void	setup_command(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	expand_wildcard_mlst(cmd->m_lst->matrix);
	ft_expand_m_lst(cmd->m_lst->matrix);
	ft_remove_quote_mlst(cmd->m_lst->matrix);
	if (ft_valid_command(cmd, mini))
		return ;
	execute(cmd, mini, var);
}

static int	ft_valid_command(t_ast_n *cmd, t_mini *mini)
{
	if (cmd->m_lst->matrix->size == 1
		&& cmd->m_lst->matrix->head->lst->size == 0)
	{
		ft_msg_error("''", " command not found");
		free_cmd_operator_executed(cmd, mini);
		return (1);
	}
	while (cmd->m_lst->matrix->head->lst->size == 0)
		ft_remove_lst_front(cmd->m_lst->matrix);
	if (cmd->m_lst->matrix->size == 0)
	{
		free_cmd_operator_executed(cmd, mini);
		return (1);
	}
	return (0);
}
