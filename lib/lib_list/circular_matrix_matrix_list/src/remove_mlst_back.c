/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_mlst_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:40:31 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:30:01 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

static int	ft_size_one(t_mtrx_mtrx *ma_lst);
static int	ft_size_two(t_mtrx_mtrx *ma_lst);
static int	ft_three_more(t_mtrx_mtrx *ma_lst);

int	ft_remove_matrix_back(t_mtrx_mtrx *ma_lst)
{
	if (!ma_lst)
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

	v.last = ma_lst->last;
	ma_lst->head = NULL;
	ma_lst->last = NULL;
	ma_lst->size--;
	if (ft_delete_matrix(v.last->matrix))
		return (-1);
	free(v.last);
	v.last = NULL;
	return (0);
}

static int	ft_size_two(t_mtrx_mtrx *ma_lst)
{
	t_var_m_mlst	v;

	v.last = ma_lst->last;
	ma_lst->head->next = ma_lst->head;
	ma_lst->head->prev = ma_lst->head;
	ma_lst->last = ma_lst->head;
	ma_lst->size--;
	if (ft_delete_matrix(v.last->matrix))
		return (-1);
	free(v.last);
	v.last = NULL;
	return (0);
}

static int	ft_three_more(t_mtrx_mtrx *ma_lst)
{
	t_var_m_mlst	v;

	v.last = ma_lst->last;
	v.second = ma_lst->last->prev;
	v.second->next = ma_lst->head;
	ma_lst->head->prev = v.last;
	ma_lst->last = v.second;
	ma_lst->size--;
	if (ft_delete_matrix(v.last->matrix))
		return (-1);
	free(v.last);
	v.last = NULL;
	return (0);
}
