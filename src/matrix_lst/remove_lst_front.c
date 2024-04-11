/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_lst_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:44:00 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/11 09:32:00 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

static int	lst_size_one(t_mtrx_lst *m_lst);
static int	lst_size_two(t_mtrx_lst *m_lst);
static int	lst_size_third_onward(t_mtrx_lst *m_lst);

int	ft_remove_lst_front(t_mtrx_lst *m_lst)
{
	t_var_matrix	var;
	
	if (!m_lst)
		return (-1);
	if (m_lst->size == 0)
		return (-1);
	if (m_lst->size == 1)
	{
		if (lst_size_one(m_lst))
			return (-1);
		return (0);
	}
	else if (m_lst->size == 2)
	{
		if (lst_size_two(m_lst))
			return (-1);
		return (0);
	}
	else if (m_lst->size > 2)
	{
		if (lst_size_third_onward(m_lst))
			return (-1);
		return (0);
	}
	return (-1);
}


static int	lst_size_one(t_mtrx_lst *m_lst)
{
	if (ft_delete_list(m_lst->head->lst))
		return (-1);
	free(m_lst->head);
	m_lst->head = NULL;
	m_lst->last = NULL;
	m_lst->size--;
	return (0);
}

static int	lst_size_two(t_mtrx_lst *m_lst)
{
	t_var_matrix	var;


	m_lst->last->next = m_lst->last;
	m_lst->last->prev = m_lst->last;
	if (ft_delete_list(m_lst->head->lst))
		return (-1);
	free(m_lst->head);
	m_lst->size--;
	m_lst->head = m_lst->last;
	return (0);
}


static int	lst_size_third_onward(t_mtrx_lst *m_lst)
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