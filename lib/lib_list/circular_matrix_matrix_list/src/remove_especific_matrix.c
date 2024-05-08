/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_especific_matrix.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:49:15 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/08 09:05:00 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

static int	ft_check_in_m_matrix(t_mmlst *m_matrix, t_mnode *node_mtrx);
static int	ft_others_cases(t_mmlst *m_matrix, t_mnode *node_mtrx);

int	ft_remove_specific_matrix(t_mmlst *m_matrix, t_mnode *node_mtrx)
{
	if (!m_matrix)
		return (-1);
	if (!m_matrix)
		return (-1);
	if (ft_check_in_m_matrix(m_matrix, node_mtrx))
		return (-1);
	if (m_matrix->head == node_mtrx)
		return (ft_remove_matrix_front(m_matrix));
	else if (m_matrix->last == node_mtrx)
		return (ft_remove_matrix_back(m_matrix));
	else
		return (ft_others_cases(m_matrix, node_mtrx));
	return (-1);
}

static int	ft_others_cases(t_mmlst *m_matrix, t_mnode *node_mtrx)
{
	t_var_m_mlst	v;

	v.next = node_mtrx->next;
	v.prev = node_mtrx->prev;
	v.next->prev = v.prev;
	v.prev->next = v.next;
	m_matrix->size--;
	if (ft_delete_matrix(node_mtrx->matrix))
		return (-1);
	free(node_mtrx);
	node_mtrx = NULL;
	return (0);
}

static int	ft_check_in_m_matrix(t_mmlst *m_matrix, t_mnode *node_mtrx)
{
	t_var_m_mlst	v;

	v.i = 1;
	v.current = m_matrix->head;
	while (v.i <= m_matrix->size)
	{
		if (v.current == node_mtrx)
			return (0);
		v.current = v.current->next;
		v.i++;
	}
	return (-1);
}
