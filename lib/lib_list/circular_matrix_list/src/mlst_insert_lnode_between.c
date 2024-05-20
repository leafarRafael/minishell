/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlst_insert_lnode_between.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:16:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/20 18:34:14 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

int	insert_lnode_between(t_mlst *mlst, t_llst *lnode, t_mlst *new_mlst)
{
	t_llst	*temp;

	if (!mlst || !lnode || !new_mlst)
		return (-1);
	if (mlst->size == 0 || new_mlst->size == 0)
		return (-1);
	if (mlst->size == 1)
	{
		lnode->next = new_mlst->head;
		new_mlst->head->prev = lnode;
		lnode->prev = new_mlst->last;
		new_mlst->last->next = lnode;
		mlst->last = new_mlst->last;
		mlst->size += new_mlst->size;	
	}
	else if (mlst->head == lnode)
	{
		temp = lnode->next;
	
		mlst->head->next = new_mlst->head;
		new_mlst->head->prev = mlst->head;
		temp->prev = new_mlst->last;
		new_mlst->last->next = temp;
		mlst->size += new_mlst->size;
	}
	else if (mlst->last == lnode)
	{
		mlst->last->next = new_mlst->head;
		new_mlst->head->prev = mlst->last;
		new_mlst->last->next = mlst->head;
		mlst->head->prev = new_mlst->head;
		mlst->last = new_mlst->last;
		mlst->size += new_mlst->size;
	}
	else
	{
		temp = lnode->next;
		lnode->next = new_mlst->head;
		new_mlst->head->prev = lnode;
		temp->prev = new_mlst->last;
		new_mlst->last->next = temp;
		mlst->size += new_mlst->size;
	}
	return (0);
}
