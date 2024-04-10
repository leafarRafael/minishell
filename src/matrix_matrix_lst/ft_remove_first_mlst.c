/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_first_mlst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:02:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/10 17:01:52 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

static void	ft_size_one(t_mtrx_mtrx *ma_lst);
static void	ft_size_two(t_mtrx_mtrx *ma_lst);
static void ft_three_more(t_mtrx_mtrx *ma_lst);

int	ft_remove_first_matrix(t_mtrx_mtrx *ma_lst)
{
	if (!ma_lst)
		return (-1);
	if (ma_lst->size == 0)
		return (-1);
	if (ma_lst->size == 1)
	{
		ft_size_one(ma_lst);
		return (0);
	}
	else if (ma_lst->size == 2)
	{
		ft_size_two(ma_lst);
		return (0);
	}
	else if (ma_lst->size > 2)
	{
		ft_three_more(ma_lst);
		return (0);
	}
	return (-1);
}

static void	ft_size_one(t_mtrx_mtrx *ma_lst)
{
	t_var_m_mlst	v;

	v.head = ma_lst->head;
	ma_lst->head = NULL;
	ma_lst->last = NULL;
	ma_lst->size--;
	ft_delete_matrix(v.head->matrix);
	free(v.head);
}

static void	ft_size_two(t_mtrx_mtrx *ma_lst)
{
	t_var_m_mlst	v;

	v.head = ma_lst->head;
	ma_lst->last->next = ma_lst->last;
	ma_lst->last->prev = ma_lst->last;
	ma_lst->head = ma_lst->last;
	ma_lst->size--;
	ft_delete_matrix(v.head->matrix);
	free(v.head);
}

static void ft_three_more(t_mtrx_mtrx *ma_lst)
{
	t_var_m_mlst	v;

	v.head = ma_lst->head;
	v.second = ma_lst->head->next;
	v.second->prev = ma_lst->last;
	ma_lst->last->prev = v.second;
	ma_lst->head = v.second;
	ma_lst->size--;
	ft_delete_matrix(v.head->matrix);
	free(v.head);
}