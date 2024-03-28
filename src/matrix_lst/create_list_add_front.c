/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_add_front.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:24:08 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/28 16:39:05 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

int	ft_create_add_list_front(t_matrix_lst *matrix_lst, t_lst_line *lst)
{
	t_var_matrix	var;

	if (!matrix_lst || !lst)
		return (-1);
	if (matrix_lst->size == 0)
	{
		lst->next = lst;
		lst->prev = lst;
		matrix_lst->head = lst;
		matrix_lst->last = lst;
		matrix_lst->size++;
		return (0);
	}
	else if (matrix_lst->size == 1)
	{
		var.last_lst = matrix_lst->head;
		lst->next = var.last_lst;
		lst->prev = var.last_lst;
		var.last_lst->next = lst;
		var.last_lst->prev = lst;
		matrix_lst->head = lst;
		matrix_lst->last = var.last_lst;
		matrix_lst->size++;
		return (0);
	}
	else
	{
		var.head_lst = matrix_lst->head;
		var.last_lst = matrix_lst->last;
		lst->prev = var.last_lst;
		lst->next = var.head_lst;
		var.last_lst->next = lst;
		var.head_lst->prev = lst;
		matrix_lst->head = lst;
		matrix_lst->size++;
		return (0);
	}
}