/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_insert_node_between.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:16:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/21 12:00:52 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

int	insert_node_between(t_lst *lst, t_node *node, t_lst *new_lst)
{
	t_node	*temp;

	if (!lst || !node || !new_lst)
		return (-1);
	if (lst->size == 0 || new_lst->size == 0)
		return (-1);
	if (lst->size == 1)
	{
		node->next = new_lst->head;
		new_lst->head->prev = node;
		node->prev = new_lst->last;
		new_lst->last->next = node;
		lst->last = new_lst->last;
		lst->size += new_lst->size;	
	}
	else if (lst->head == node)
	{
		temp = node->next;
	
		lst->head->next = new_lst->head;
		new_lst->head->prev = lst->head;
		temp->prev = new_lst->last;
		new_lst->last->next = temp;
		lst->size += new_lst->size;
	}
	else if (lst->last == node)
	{
		lst->last->next = new_lst->head;
		new_lst->head->prev = lst->last;
		new_lst->last->next = lst->head;
		lst->head->prev = new_lst->head;
		lst->last = new_lst->last;
		lst->size += new_lst->size;
	}
	else
	{
		temp = node->next;
		node->next = new_lst->head;
		new_lst->head->prev = node;
		temp->prev = new_lst->last;
		new_lst->last->next = temp;
		lst->size += new_lst->size;
	}
	return (0);
}
