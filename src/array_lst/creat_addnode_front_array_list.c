/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_addnode_front_array_list.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:43:41 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/22 14:35:03 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static void	ft_first_node(t_array_lst *lst, t_node_alst *new_node);
static void	ft_second_node(t_array_lst *lst, t_node_alst *new_node);
static void	ft_third_onwards_node(t_array_lst *lst, t_node_alst *new_node);

int	ft_create_addnode_front_alst(t_array_lst *lst, char content)
{
	t_node_alst	*new_node;

	if (!lst)
		return (-1);
	new_node = malloc(sizeof(t_node_alst));
	if (!new_node)
		return (-1);
	new_node->c = content;
	if (lst->size == 0)
	{
		ft_first_node(lst, new_node);
		return (0);
	}
	else if (lst->size == 1)
	{
		ft_second_node(lst, new_node);
		return (0);
	}
	else
	{
		ft_third_onwards_node(lst, new_node);
		return (0);
	}
}

static void	ft_first_node(t_array_lst *lst, t_node_alst *new_node)
{
	new_node->next = new_node;
	new_node->prev = new_node;
	lst->head = new_node;
	lst->last = new_node;
	lst->size = 1;
}

static void	ft_second_node(t_array_lst *lst, t_node_alst *new_node)
{
	new_node->next = lst->last;
	new_node->prev = lst->last;
	lst->last->prev = new_node;
	lst->last->next = new_node;
	lst->head = new_node;
	lst->size++;
}

static void	ft_third_onwards_node(t_array_lst *lst, t_node_alst *new_node)
{
	t_var	var;

	var.head = lst->head;
	var.head = lst->head;
	new_node->next = var.head;
	new_node->prev = lst->last;
	lst->last->next = new_node;
	var.head->prev = new_node;
	lst->head = new_node;
	lst->size++;
}
