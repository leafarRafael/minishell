/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_lst_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:44:00 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/29 16:56:53 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

int	ft_remove_lst_front(t_matrix_lst *m_lst)
{
	if (!m_lst)
		return (-1);
	if (m_lst->size == 1)
	{
		if (ft_delete_list(m_lst->head->lst))
			return (-1);
		m_lst->head = NULL;
		m_lst->last = NULL;
		m_lst->size--;
		return (0);
	}
	if (m_lst->size == 2)
	{
		t_var_matrix	var;

		var.last_lst = m_lst->last;
		var.last_lst->next = var.last_lst;
		var.last_lst->prev = var.last_lst;
		if (ft_delete_list(m_lst->head->lst))
			return (-1);
		free(var.head_lst);
		m_lst->head = var.last_lst;
		return (0);
	}
	else
	{
		t_var_matrix	var;

		var.head_lst = m_lst->head;
		var.last_lst = m_lst->last;
		var.second_lst = m_lst->head->next;
		var.second_lst->prev = var.last_lst;
		var.last_lst->next - var.second_lst;
		if (ft_delete_list(var.head_lst->lst))
			return (-1);
		free(var.head_lst);
		return (0);
	}
}