/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_node_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:51:10 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/22 13:37:12 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static int	ft_one_node(t_array_lst *lst);
static int	ft_two_node(t_array_lst *lst);
static int	ft_three_more_node(t_array_lst *lst);

int	ft_remove_node_front(t_array_lst *lst)
{
	if (!lst)
		return (-1);
	if (!lst->head && !lst->last)
		return (-1);
	if (lst->size == 1)
		return (ft_one_node(lst));
	else if (lst->size == 2)
		return (ft_two_node(lst));
	else
		return (ft_three_more_node(lst));
	return (-1);	
}

static int	ft_one_node(t_array_lst *lst)
{
	t_var	var;

	var.head = lst->head;
	lst->head = NULL;
	lst->last = NULL;
	lst->size = 0;
	free(var.head);
	return (0);
}

static int	ft_two_node(t_array_lst *lst)
{
	t_var	var;

	var.head = lst->head;
	var.last = lst->last;
	var.last->next = var.last;
	var.last->prev = var.last;
	lst->head = var.last;
	lst->size--;
	free(var.head);
	return (0);
}

static int	ft_three_more_node(t_array_lst *lst)
{
	t_var	var;

	var.head = lst->head;
	var.second = var.head->next;
	var.second->prev = lst->last;
	lst->last->next = var.second;
	lst->head = var.second;
	lst->size--;
	free(var.head);
	return (0);
}
