/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_lst_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:44:00 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:19:35 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

static int	remove_one_size(t_mtrx_lst *matrix);
static int	remove_two_size(t_mtrx_lst *matrix);
static int	remove_size_three_more(t_mtrx_lst *matrix);

int	ft_remove_lst_front(t_mtrx_lst *m_lst)
{
	if (!m_lst)
		return (-1);
	if (m_lst->size == 0)
		return (-1);
	if (m_lst->size == 1)
	{
		if (remove_one_size(m_lst))
			return (-1);
		return (0);
	}
	if (m_lst->size == 2)
	{
		if (remove_two_size(m_lst))
			return (-1);
		return (0);
	}
	if (m_lst->size > 2)
	{
		if (remove_size_three_more(m_lst))
			return (-1);
		return (0);
	}
	return (-1);
}

static int	remove_one_size(t_mtrx_lst *matrix)
{
	t_var_matrix	v;

	v.head_lst = matrix->head;
	matrix->head = NULL;
	matrix->last = NULL;
	matrix->size--;
	if (ft_delete_list(v.head_lst->lst))
		return (-1);
	free(v.head_lst);
	v.head_lst = NULL;
	return (0);
}

static int	remove_two_size(t_mtrx_lst *matrix)
{
	t_var_matrix	v;

	v.head_lst = matrix->head;
	matrix->last->next = matrix->last;
	matrix->last->prev = matrix->last;
	matrix->head = matrix->last;
	matrix->size--;
	if (ft_delete_list(v.head_lst->lst))
		return (-1);
	free(v.head_lst);
	v.head_lst = NULL;
	return (0);
}

static int	remove_size_three_more(t_mtrx_lst *matrix)
{
	t_var_matrix	v;

	v.second_lst = matrix->head->next;
	v.head_lst = matrix->head;
	v.second_lst->prev = matrix->last;
	matrix->last->next = matrix->head;
	matrix->head = v.second_lst;
	matrix->size--;
	if (ft_delete_list(v.head_lst->lst))
		return (-1);
	free(v.head_lst);
	v.head_lst = NULL;
	return (0);
}
