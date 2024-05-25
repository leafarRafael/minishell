/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlst_insert_lnode_between.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:16:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/24 14:49:17 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

int	insert_lnode_between(t_mlst *mlst, t_llst *lnode, t_mlst *mtrx)
{
	t_llst	*temp;

	if (!mlst || !lnode || !mtrx)
		return (-1);
	if (mlst->size == 0 || mtrx->size == 0)
		return (-1);
	if (mlst->size == 1)
	{
		lnode->next = mtrx->head;
		mtrx->head->prev = lnode;
		lnode->prev = mtrx->last;
		mtrx->last->next = lnode;
		mlst->last = mtrx->last;
		mlst->size += mtrx->size;	
	}
	else if (mlst->head == lnode)
	{
		temp = lnode->next;
		mlst->head->next = mtrx->head;
		mtrx->head->prev = mlst->head;
		temp->prev = mtrx->last;
		mtrx->last->next = temp;
		mlst->size += mtrx->size;
	}
	else if (mlst->last == lnode)
	{
		mlst->last->next = mtrx->head;
		mtrx->head->prev = mlst->last;		
		mlst->head->prev = mtrx->last;
		mtrx->last->next = mlst->head;	
		mlst->last = mtrx->last;
		mlst->size += mtrx->size;
	}
	else
	{
		temp = lnode->next;
		lnode->next = mtrx->head;
		mtrx->head->prev = lnode;
		temp->prev = mtrx->last;
		mtrx->last->next = temp;
		mlst->size += mtrx->size;
	}
	return (0);
}
