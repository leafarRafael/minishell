/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_lst_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:44:00 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/01 09:58:39 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

static int	lst_size_one(t_matrix_lst *m_lst);
static int	lst_size_two(t_matrix_lst *m_lst);
static int	lst_size_third_onward(t_matrix_lst *m_lst);

int	ft_remove_lst_front(t_matrix_lst *m_lst)
{
	t_var_matrix	var;
	
	if (!m_lst)
		return (-1);
	if (m_lst->size == 0)
		return (-1);
	if (m_lst->size == 1)
	{
		if (lst_size_one(m_lst));
			return (-1);
		return (0);
	}
	else if (m_lst->size == 2)
	{
		if (lst_size_two(m_lst));
			return (-1);
		return (0);
	}
	else
	{
		if (lst_size_third_onward(m_lst));
			return (-1);
		return (0);
	}
	return (-1);
}


static int	lst_size_one(t_matrix_lst *m_lst)
{
	if (ft_delete_list(m_lst->head->lst))
		return (-1);
	m_lst->head = NULL;
	m_lst->last = NULL;
	m_lst->size--;
	return (0);
}

static int	lst_size_two(t_matrix_lst *m_lst)
{
	t_var_matrix	var;

	var.head_lst = m_lst->head;
	var.last_lst = m_lst->last;
	var.last_lst->next = var.last_lst;
	var.last_lst->prev = var.last_lst;
	m_lst->head = var.last_lst;
	if (ft_delete_list(m_lst->head->lst))
		return (-1);
	free(var.head_lst);
	m_lst->size--;
	return (0);
}


static int	lst_size_third_onward(t_matrix_lst *m_lst)
{
	t_var_matrix	var;

	var.head_lst = m_lst->head;
	var.second_lst = m_lst->head->next;
	var.second_lst->prev = m_lst->last;
	m_lst->last->next = var.second_lst;
	m_lst->head = var.second_lst;
	if (ft_delete_list(var.head_lst->lst))
		return (-1);
	free(var.head_lst);
	m_lst->size--;
	return (0);
}