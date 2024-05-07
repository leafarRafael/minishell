/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_lst_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 08:21:49 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 08:29:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

static int	remove_one_size(t_mlst *matrix);
static int	remove_two_size(t_mlst *matrix);
static int	remove_size_three_more(t_mlst *matrix);

int	ft_remove_list_back(t_mlst *m_lst)
{
	if (!m_lst)
		return (-1);
	if (m_lst->size == 0)
		return (-1);
	if (m_lst->size == 1)
		return (remove_one_size(m_lst));
	if (m_lst->size == 2)
		return (remove_two_size(m_lst));
	if (m_lst->size > 2)
		return (remove_size_three_more(m_lst));
	return (-1);
}

static int	remove_one_size(t_mlst *matrix)
{
	t_var_matrix	v;

	v.last_lst = matrix->last;
	matrix->head = NULL;
	matrix->last = NULL;
	matrix->size--;
	if (ft_delete_list(v.last_lst->lst))
		return (-1);
	free(v.last_lst);
	v.last_lst = NULL;
	return (0);
}

static int	remove_two_size(t_mlst *matrix)
{
	t_var_matrix	v;

	v.last_lst = matrix->last;
	matrix->head->next = matrix->head;
	matrix->head->prev = matrix->head;
	matrix->last = matrix->head;
	matrix->size--;
	if (ft_delete_list(v.last_lst->lst))
		return (-1);
	free(v.last_lst);
	v.last_lst = NULL;
	return (0);
}

static int	remove_size_three_more(t_mlst *matrix)
{
	t_var_matrix	v;

	v.second_lst = matrix->last->prev;
	v.last_lst = matrix->last;
	v.second_lst->next = matrix->head;
	matrix->head->prev = v.second_lst;
	matrix->last = v.second_lst;
	matrix->size--;
	if (ft_delete_list(v.last_lst->lst))
		return (-1);
	free(v.last_lst);
	v.last_lst = NULL;
	return (0);
}
