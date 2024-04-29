/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_m_front.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:56:33 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:34:43 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

static void	ft_first(t_mtrx_mtrx *lst_m, t_mnode *new_mnode);
static void	ft_second(t_mtrx_mtrx *lst_m, t_mnode *new_mnode);
static void	ft_third_onwards(t_mtrx_mtrx *lst_m, t_mnode *new_mnode);

int	ft_matrix_add_front(t_mtrx_mtrx *lst_m, t_mtrx_lst *matrix)
{
	t_mnode			*new_mnode;

	if (!lst_m || !matrix)
		return (-1);
	new_mnode = init_matrix_node();
	new_mnode->matrix = matrix;
	if (lst_m->size == 0)
	{
		ft_first(lst_m, new_mnode);
		return (0);
	}
	else if (lst_m->size == 1)
	{
		ft_second(lst_m, new_mnode);
		return (0);
	}
	else if (lst_m->size > 1)
	{
		ft_third_onwards(lst_m, new_mnode);
		return (0);
	}
	return (-1);
}

static void	ft_first(t_mtrx_mtrx *lst_m, t_mnode *new_mnode)
{
	new_mnode->next = new_mnode;
	new_mnode->prev = new_mnode;
	lst_m->head = new_mnode;
	lst_m->last = new_mnode;
	lst_m->size++;
}

static void	ft_second(t_mtrx_mtrx *lst_m, t_mnode *new_mnode)
{
	new_mnode->prev = lst_m->last;
	new_mnode->next = lst_m->last;
	lst_m->last->prev = new_mnode;
	lst_m->last->next = new_mnode;
	lst_m->head = new_mnode;
	lst_m->size++;
}

static void	ft_third_onwards(t_mtrx_mtrx *lst_m, t_mnode *new_mnode)
{
	new_mnode->prev = lst_m->last;
	new_mnode->next = lst_m->head;
	lst_m->last->next = new_mnode;
	lst_m->head->prev = new_mnode;
	lst_m->head = new_mnode;
	lst_m->size++;
}
