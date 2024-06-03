/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlst_insert_lnode_between.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:16:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/03 14:30:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

static int	ft_size_one(t_mlst *mlst, t_llst *lnode, t_mlst *mtrx);
static int	ft_case_head(t_mlst *mlst, t_llst *lnode, t_mlst *mtrx);
static int	ft_case_last(t_mlst *mlst, t_mlst *mtrx);
static int	ft_others(t_mlst *mlst, t_llst *lnode, t_mlst *mtrx);

int	insert_lnode_between(t_mlst *mlst, t_llst *lnode, t_mlst *mtrx)
{
	if (!mlst || !lnode || !mtrx)
		return (-1);
	if (mlst->size == 0 || mtrx->size == 0)
		return (-1);
	if (mlst->size == 1)
		return (ft_size_one(mlst, lnode, mtrx));
	else if (mlst->head == lnode)
		return (ft_case_head(mlst, lnode, mtrx));
	else if (mlst->last == lnode)
		return (ft_case_last(mlst, mtrx));
	return (ft_others(mlst, lnode, mtrx));
}

static int	ft_size_one(t_mlst *mlst, t_llst *lnode, t_mlst *mtrx)
{
	lnode->next = mtrx->head;
	mtrx->head->prev = lnode;
	lnode->prev = mtrx->last;
	mtrx->last->next = lnode;
	mlst->last = mtrx->last;
	mlst->size += mtrx->size;
	return (0);
}

static int	ft_case_head(t_mlst *mlst, t_llst *lnode, t_mlst *mtrx)
{
	t_llst	*temp;

	temp = lnode->next;
	mlst->head->next = mtrx->head;
	mtrx->head->prev = mlst->head;
	temp->prev = mtrx->last;
	mtrx->last->next = temp;
	mlst->size += mtrx->size;
	return (0);
}

static int	ft_case_last(t_mlst *mlst, t_mlst *mtrx)
{
	mlst->last->next = mtrx->head;
	mtrx->head->prev = mlst->last;
	mlst->head->prev = mtrx->last;
	mtrx->last->next = mlst->head;
	mlst->last = mtrx->last;
	mlst->size += mtrx->size;
	return (0);
}

static int	ft_others(t_mlst *mlst, t_llst *lnode, t_mlst *mtrx)
{
	t_llst	*temp;

	temp = lnode->next;
	lnode->next = mtrx->head;
	mtrx->head->prev = lnode;
	temp->prev = mtrx->last;
	mtrx->last->next = temp;
	mlst->size += mtrx->size;
	return (0);
}
