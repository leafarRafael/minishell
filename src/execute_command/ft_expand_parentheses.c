/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_parentheses.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:25:07 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/19 12:06:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void remove_parent(t_lst *new_lst);
static void add_new_token(t_lst *new_lst, t_ast_n *cmd, t_mini *mini);

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
	add_new_token(new_lst, cmd, mini);
	ft_parse_exe(new_lst, mini);
}

static void add_new_token(t_lst *new_lst, t_ast_n *cmd, t_mini *mini)
{
	t_mmlst		*new_mmlst;
	t_mnode		*temp;

	new_mmlst = init_mmlst();
	while (new_lst->size > 0)
		ft_mmlst_add_back(new_mmlst, ft_token_cmd(new_lst));
	if (mini->mmlst->size == 1)
	{
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
		mini->mmlst->head = new_mmlst->head;
		mini->mmlst->last = new_mmlst->last;
		mini->mmlst->size = new_mmlst->size;	
	}
	else if (mini->mmlst->head == cmd->m_lst)
	{
		temp = cmd->m_lst->next;
		mini->mmlst->head->next = new_mmlst->head;
		temp->prev = new_mmlst->last;
		new_mmlst->head->prev = mini->mmlst->head;
		new_mmlst->last->next = temp;
		mini->mmlst->size += new_mmlst->size;
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
	}
	else if (mini->mmlst->last == cmd->m_lst)
	{
		temp = mini->mmlst->last->prev;
		temp->next = new_mmlst->head;
		new_mmlst->head->prev = temp;
		new_mmlst->last->next = mini->mmlst->last;
		mini->mmlst->last->prev = new_mmlst->last;
		mini->mmlst->size += new_mmlst->size;
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
	}
	else
	{
		temp = cmd->m_lst->next;
		cmd->m_lst->next = new_mmlst->head;
		new_mmlst->head->prev = cmd->m_lst;
		temp->prev = new_mmlst->last;
		new_mmlst->last->next = temp;
		mini->mmlst->size += new_mmlst->size;
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
	}
	if (new_lst)
	{
		free(new_lst);
		new_lst = NULL;
	}
	free(new_mmlst);
	new_mmlst = NULL;
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