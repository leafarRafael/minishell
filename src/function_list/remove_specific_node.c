/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_specific_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:32:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/01 16:06:40 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static int	ft_one_node(t_lst *lst, t_node *node);
static int	ft_two_node(t_lst *lst, t_node *node);
static int	ft_three_more_node(t_lst *lst, t_node *node);
static int	ft_case_head_last(t_lst *lst, t_node *node);

int	ft_remove_specific_node(t_lst *lst, t_node *node)
{
	if (!lst)
		return (-1);
	if (!node)
		return (-1);
	if (!lst->head && lst->last)
		return (-1);
	if (lst->size == 0)
		return (-1);
	if (lst->size == 1)
		return (ft_one_node(lst, node));
	else if (lst->size == 2)
		return (ft_two_node(lst, node));
	else if (lst->size > 2)
		return (ft_three_more_node(lst, node));
	return (-1);
}

static int	ft_one_node(t_lst *lst, t_node *node)
{
	lst->last = NULL;
	lst->head = NULL;
	lst->size = 0;
	free(node);	
	return (0);
}

static int	ft_two_node(t_lst *lst, t_node *node)
{
	t_var var;

	if (node == lst->head)
	{
		ft_remove_node_front(lst);
		return (0);
	}
	if (node == lst->last)
	{
		ft_remove_node_back(lst);
		return (0);
	}
	return (-1);
}

static int	ft_three_more_node(t_lst *lst, t_node *node)
{
	t_var var;

	if (node == lst->head || node == lst->last)
		return (ft_case_head_last(lst, node));
	var.current_node = lst->head;
	var.next_node = var.current_node->next;
	var.i = 0;
	while (var.i <= lst->size)
	{
		var.prev_node = var.current_node;
		var.current_node = var.next_node;
		var.next_node = var.next_node->next;
		var.i++;
		if (node == var.current_node)
			break ;
	}
	var.prev_node->next = var.next_node;
	var.next_node->prev = var.prev_node;
	free(node);
	lst->size--;
	return (0);
}

static int	ft_case_head_last(t_lst *lst, t_node *node)
{
	t_var var;

	if (node == lst->head)
	{
		ft_remove_node_front(lst);
		return (0);
	}
	if (node == lst->last)
	{
		ft_remove_node_back(lst);
		return (0);
	}
	return (-1);
}