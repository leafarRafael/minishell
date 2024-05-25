/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_and_return_lline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:05:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/24 18:51:28 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

static t_llst *ft_size_one(t_mlst *mlst, t_llst *lnode);

t_llst	*ft_remove_return_mlst_node(t_mlst *mlst, t_llst *lnode)
{
	t_var_matrix	var;

	if (!mlst || !lnode)
		return (NULL);
	if (!mlst->head || !mlst->last || mlst->size == 0)
		return (NULL);
	if (lnode->next == lnode)
		return (ft_size_one(mlst, lnode));
	var.next_lst = lnode->next;
	var.prev_lst = lnode->prev;
	var.prev_lst->next = var.next_lst;
	var.next_lst->prev = var.prev_lst;
	if (lnode == mlst->head)
		mlst->head = var.next_lst;
	if (lnode == mlst->last)
		mlst->last = var.prev_lst;
	lnode->next = NULL;
	lnode->prev = NULL;
	mlst->size--;
	return (lnode);
}

static t_llst *ft_size_one(t_mlst *mlst, t_llst *lnode)
{
	mlst->head = NULL;
	mlst->last = NULL;
	lnode->next = NULL;
	lnode->prev = NULL;
	mlst->size--;
	return (lnode);
}
