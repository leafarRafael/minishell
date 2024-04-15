/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_nodes_between.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:16:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/15 09:29:30 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static void	empyt_list_dest(t_lst *lst_dest, t_node *between_a, t_node *between_b, t_lst *lst_new);
static void	list_dest_size_one(t_lst *lst_dest, t_lst *lst_new);
static void	list_dest_size_two_more(t_node *between_a, t_node *between_b, t_lst *lst_new);
static int	node_in_list(t_lst *lst_dest, t_node *node);

int	ft_insert_lst_between_lst(t_lst *lst_dest, t_node *between_a, t_node *between_b, t_lst *lst_new)
{
	if (!lst_dest || !lst_new || !between_a || !between_b)
		return (-1);
	if (lst_dest == lst_new)
		return (-1);
	if (lst_dest->size == 0)
	{
		empyt_list_dest(lst_dest, between_a, between_b, lst_new);
		return (0);
	}
	if (node_in_list(lst_dest, between_a) || node_in_list(lst_dest, between_a))
		return (-1);
	if (between_a->next != between_b && between_b->prev != between_a)
			return (-1);
	if (lst_dest->size == 1)
	{
		list_dest_size_one(lst_dest, lst_new);
		return (0);
	}
	if (lst_dest->size >= 2)
	{
		if (between_a == between_b)
			return (-1);
		list_dest_size_two_more(between_a, between_b, lst_new);
		lst_dest->size += lst_new->size;
		lst_new->size = 0;
	}
	return (-1);
}

static void	empyt_list_dest(t_lst *lst_dest, t_node *between_a, t_node *between_b, t_lst *lst_new)
{
	between_a = lst_new->head;
	between_b = lst_new->last;
	lst_dest->head = between_a;
	lst_dest->last = between_b;
	lst_dest->size = lst_new->size;
	lst_new->size = 0;
}

static void	list_dest_size_one(t_lst *lst_dest, t_lst *lst_new)
{
	lst_dest->head->next = lst_new->head;
	lst_new->head->prev = lst_dest->head;
	lst_new->last->next = lst_dest->head;
	lst_dest->head->prev = lst_new->last;
	lst_dest->last = lst_new->last;
	lst_dest->size += lst_new->size;
	lst_new->size = 0;
}

static void	list_dest_size_two_more(t_node *between_a, t_node *between_b, t_lst *lst_new)
{
	between_a->next = lst_new->head;
	lst_new->head->prev = between_a;
	between_b->prev = lst_new->last;
	lst_new->last->next = between_b;
}

static int	node_in_list(t_lst *lst_dest, t_node *node)
{
	t_var	var;

	var.current_node = lst_dest->head;
	var.i = 1;
	while (var.i <= lst_dest->size)
	{
		if (var.current_node == node)
			return (0);
		var.current_node = var.current_node->next;
		var.i++;
	}
	return (-1);
}