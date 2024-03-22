/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_node_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:16:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/22 13:34:44 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static int	ft_one_node(t_array_lst *lst);
static int	ft_two_node(t_array_lst *lst);
static int	ft_three_more_node(t_array_lst *lst);

int	ft_remove_node_back(t_array_lst *lst)
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

	var.last = lst->last;
	lst->last = NULL;
	lst->head = NULL;
	lst->size = 0;
	free(var.last);	
	return (0);
}

static int	ft_two_node(t_array_lst *lst)
{
	t_var	var;

	var.head = lst->head;
	var.last = lst->last;
	var.head->next = var.head;
	var.head->prev = var.head;
	lst->last = var.head;
	lst->size--;
	free (var.last);
	return (0);
}

static int	ft_three_more_node(t_array_lst *lst)
{
	t_var	var;

	var.last = lst->last;
	var.second_last = var.last->prev;
	var.second_last->next = lst->head;
	lst->head->prev = var.second_last;
	lst->last = var.second_last;
	lst->size--;
	free(var.last);
	return (0);
}
