/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_specific_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:32:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/22 12:34:50 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static int	ft_one_node(t_array_lst *lst, t_node_alst *node);
static int	ft_two_node(t_array_lst *lst, t_node_alst *node);
static int	ft_three_more_node(t_array_lst *lst, t_node_alst *node);
static int	ft_case_head_last(t_array_lst *lst, t_node_alst *node);

int	ft_remove_specific_node(t_array_lst *lst, t_node_alst *node)
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

static int	ft_one_node(t_array_lst *lst, t_node_alst *node)
{
	lst->last = NULL;
	lst->head = NULL;
	lst->size = 0;
	free(node);	
	return (0);
}

static int	ft_two_node(t_array_lst *lst, t_node_alst *node)
{
	t_var var;

	if (node == lst->head)
	{
		var.temp_node = lst->last;
		var.temp_node->prev = var.temp_node;
		var.temp_node->next = var.temp_node;
		lst->head = var.temp_node;
		lst->size--;
		free(node);
		return (0);
	}
	if (node == lst->last)
	{
		var.temp_node = lst->head;
		var.temp_node->prev = var.temp_node;
		var.temp_node->next = var.temp_node;
		lst->last = var.temp_node;
		lst->size--;
		free(node);
		return (0);
	}
	return (-1);
}

static int	ft_three_more_node(t_array_lst *lst, t_node_alst *node)
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

static int	ft_case_head_last(t_array_lst *lst, t_node_alst *node)
{
	t_var var;

	if (node == lst->head)
	{
		var.second = node->next;
		var.second->prev = lst->last;
		lst->last->next = var.second;
		lst->head = var.second;
		lst->size--;
		free(node);	
		return (0);
	}
	if (node == lst->last)
	{
		var.second_last = node->prev;
		var.second_last->next = lst->head;
		lst->head->prev = var.second_last;
		lst->last = var.second_last;
		lst->size--;
		free(node);
		return (0);
	}
	return (-1);
}