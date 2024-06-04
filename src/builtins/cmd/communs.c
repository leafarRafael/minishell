/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:00:31 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 17:29:24 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_manager_fd_builtin(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[1], STDOUT_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
	if (ft_redirect_manager(cmd->m_lst->matrix) < 0)
		free_memory(mini, var, g_status_child);
}

void	ft_valid_command_builtin(t_ast_n *cmd)
{
	if (cmd->m_lst->matrix->size == 1
		&& cmd->m_lst->matrix->head->lst->size == 0)
		ft_msg_error("''", " command not found");
	if (cmd->m_lst->matrix->size == 0)
		return ;
}

void	finished_builtin(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->next->type == PIPE || cmd->m_lst->prev_pipe)
	{
		rl_clear_history();
		free_memory(mini, var, g_status_child);
	}
}

char	*get_prfx(t_node *ptr, t_lst *lst)
{
	t_node	*temp;
	t_lst	*lst_prefix;
	char	*prefix;

	if (!lst || !ptr)
		return (NULL);
	if (ptr == lst->head)
		return (NULL);
	temp = ptr->prev;
	lst_prefix = ft_init_lst();
	while (1)
	{
		ft_add_node_front(lst_prefix, ft_cpynode(temp));
		temp = temp->prev;
		if (temp == lst->last)
			break ;
		if (temp->type == WILDCARD)
			break ;
		if (temp->type != NO_OP_TYPE)
			break ;
	}
	prefix = ft_cpy_lst_to_array(lst_prefix);
	ft_delete_list(lst_prefix);
	return (prefix);
}
