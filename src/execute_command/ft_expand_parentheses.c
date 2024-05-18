/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_parentheses.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:25:07 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/18 13:12:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void remove_parent(t_lst *new_lst);

void ft_expand_subshell(t_ast_n *cmd, t_mini *mini, t_ast *ast)
{
	t_lst		*new_lst;
	t_lst		*temp;
	t_lst		*temp2;

	if (cmd->m_lst->prev->type == AND_OP && status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && status_child == 0)
		return ;
	temp = cmd->m_lst->matrix->head->lst;
	new_lst = ft_duplst(temp, ft_cpynode, ft_add_node_back);
	remove_parent(new_lst);
	if (cmd->m_lst->next->type & (PIPE | AND_OP | OR_OP))
	{
		temp2 = cmd->m_lst->next->matrix->head->lst;
		ft_add_node_back(new_lst, temp2->head);
		if (temp2->size == 1)
			ft_add_node_back(new_lst, temp2->head);
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst->next);
	}
	ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
	ft_parse_exe(new_lst, mini);

}

static void remove_parent(t_lst *new_lst)
{
	int		i;
	t_node	*node;
	t_node	*next;
	int		parentheses;

	i = 1;
	parentheses = new_lst->head->paren;
	ft_remove_node_front(new_lst);
	node = new_lst->head;
	next = node->next;
	while (i <= new_lst->size)
	{
		if (node->paren == parentheses)
		{
			ft_remove_specific_node(new_lst, node);
			break ;
		}
		node = next;
		next = next->next;
		i++;
	}
}