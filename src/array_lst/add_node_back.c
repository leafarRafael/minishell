/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:13:20 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/22 15:16:29 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static void	ft_first_node(t_array_lst *lst, t_node_alst *node);
static void	ft_second_node(t_array_lst *lst, t_node_alst *node);
static void	ft_third_onwards_node(t_array_lst *lst, t_node_alst *node);

int	ft_addnode_back(t_array_lst *lst, t_node_alst *node)
{
	if (!lst)
		return (-1);
	if (lst->size == 0)
	{
		ft_first_node(lst, node);
		return (0);
	}
	else if (lst->size == 1)
	{
		ft_second_node(lst, node);
		return (0);
	}
	else
	{
		ft_third_onwards_node(lst, node);
		return (0);
	}
}

static void	ft_first_node(t_array_lst *lst, t_node_alst *node)
{
	node->next = node;
	node->prev = node;
	lst->head = node;
	lst->last = node;
	lst->size = 1;
}

static void	ft_second_node(t_array_lst *lst, t_node_alst *node)
{
	node->next = lst->head;
	node->prev = lst->head;
	lst->head->next = node;
	lst->head->prev = node;
	lst->last = node;
	lst->size++;
}

static void	ft_third_onwards_node(t_array_lst *lst, t_node_alst *node)
{
	t_var	var;

	var.last = lst->last;
	node->prev = var.last;
	node->next = lst->head;
	lst->head->prev = node;
	var.last->next = node;
	lst->last = node;
	lst->size++;
}
