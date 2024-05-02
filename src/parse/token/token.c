/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:31:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/02 08:41:29 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "minishell.h"

static void	muve_node_token_command(t_lst *lst, t_mtrx_lst *matrix);
static void	muve_node_token_operator(t_lst *lst, t_mtrx_lst *matrix);
static void	muve_token_parent(t_lst *lst, t_mtrx_lst *matrix);

t_mtrx_lst	*ft_simple_comand(t_lst	*lst)
{
	t_token			v;
	t_mtrx_lst		*new_matrix;

	if (!lst)
		return (NULL);
	if (lst->size == 0)
		return (NULL);
	while (lst->last->type == WH_SPACE)
		ft_remove_node_back(lst);
	while (lst->head->type == WH_SPACE)
		ft_remove_node_front(lst);
	new_matrix = ft_init_matrix();
	if (lst->head->type == OPEN_PAREN)
	{
		muve_token_parent(lst, new_matrix);
		return (new_matrix);
	}
	if (is_operator(lst->head->type))
	{
		muve_node_token_operator(lst, new_matrix);
		return (new_matrix);
	}
	else
		muve_node_token_command(lst, new_matrix);
	return (new_matrix);
}

static void	muve_node_token_command(t_lst *lst, t_mtrx_lst *matrix)
{
	t_token	v;

	if (lst->size == 0)
		return ;
	while (lst->head->type == WH_SPACE)
		ft_remove_node_front(lst);
	if (is_operator(lst->head->type))
		return ;
	v.new_lst = ft_init_lst();
	while (!is_operator(lst->head->type) && lst->head->type != WH_SPACE)
	{
		if (is_operator_redirect(lst->head->type))
		{
			if (v.new_lst->size > 0)
				break ;
			while (is_operator_redirect(lst->head->type))
			{
				v.node = ft_remove_return_node(lst, lst->head);
				ft_add_node_back(v.new_lst, v.node);
			}
			break ;
		}
		v.node = ft_remove_return_node(lst, lst->head);
		ft_add_node_back(v.new_lst, v.node);
		if (lst->size == 0)
			break ;
	}
	ft_add_list_back(matrix, v.new_lst);
	muve_node_token_command(lst, matrix);
}

static void	muve_node_token_operator(t_lst *lst, t_mtrx_lst *matrix)
{
	t_token	v;

	if (lst->size == 0)
		return ;
	while (lst->head->type == WH_SPACE)
		ft_remove_node_front(lst);
	v.type = lst->head->type;
	v.new_lst = ft_init_lst();
	while (lst->head->type == v.type)
	{
		v.node = ft_remove_return_node(lst, lst->head);
		ft_add_node_back(v.new_lst, v.node);
		if (lst->size == 0)
			break ;
		if (v.type == OPEN_PAREN || v.type == CLOSE_PAREN)
			break ;
	}
	ft_add_list_back(matrix, v.new_lst);
}

static void	muve_token_parent(t_lst *lst, t_mtrx_lst *matrix)
{
	t_token	v;
	int		parent;

	if (!lst)
		return ;
	if (lst->size == 0)
		return ;
	v.new_lst = ft_init_lst();
	parent = lst->head->paren;
	v.node = ft_remove_return_node(lst, lst->head);
	ft_add_node_back(v.new_lst, v.node);
	while (lst->head->paren != parent)
	{
		v.node = ft_remove_return_node(lst, lst->head);
		ft_add_node_back(v.new_lst, v.node);
		if (lst->head->paren == parent)
		{
			v.node = ft_remove_return_node(lst, lst->head);
			ft_add_node_back(v.new_lst, v.node);
			break ;
		}
		if (lst->size == 0)
			break ;
	}
	ft_add_list_back(matrix, v.new_lst);
}
