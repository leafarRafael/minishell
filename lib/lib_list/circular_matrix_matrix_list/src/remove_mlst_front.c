/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_mlst_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:02:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:32:38 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

static int	ft_size_one(t_mtrx_mtrx *ma_lst);
static int	ft_size_two(t_mtrx_mtrx *ma_lst);
static int	ft_three_more(t_mtrx_mtrx *ma_lst);

int	ft_remove_matrix_front(t_mtrx_mtrx *ma_lst)
{
	if (!ma_lst)
		return (-1);
	if (ma_lst->size == 0)
		return (-1);
	if (ma_lst->size == 1)
		return (ft_size_one(ma_lst));
	if (ma_lst->size == 2)
		return (ft_size_two(ma_lst));
	if (ma_lst->size > 2)
		return (ft_three_more(ma_lst));
	return (-1);
}

static int	ft_size_one(t_mtrx_mtrx *ma_lst)
{
	t_var_m_mlst	v;

	v.head = ma_lst->head;
	ma_lst->head = NULL;
	ma_lst->last = NULL;
	ma_lst->size--;
	ft_delete_matrix(v.head->matrix);
	free(v.head);
	v.head = NULL;
	return (0);
}

static int	ft_size_two(t_mtrx_mtrx *ma_lst)
{
	t_var_m_mlst	v;

	v.head = ma_lst->head;
	ma_lst->last->next = ma_lst->last;
	ma_lst->last->prev = ma_lst->last;
	ma_lst->head = ma_lst->last;
	ma_lst->size--;
	if (ft_delete_matrix(v.head->matrix))
		return (-1);
	free(v.head);
	v.head = NULL;
	return (0);
}

static int	ft_three_more(t_mtrx_mtrx *ma_lst)
{
	t_var_m_mlst	v;

	v.head = ma_lst->head;
	v.second = ma_lst->head->next;
	v.second->prev = ma_lst->last;
	ma_lst->last->prev = v.second;
	ma_lst->head = v.second;
	ma_lst->size--;
	if (ft_delete_matrix(v.head->matrix))
		return (-1);
	free(v.head);
	v.head = NULL;
	return (0);
}
