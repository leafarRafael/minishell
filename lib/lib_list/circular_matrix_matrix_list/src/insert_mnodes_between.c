/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_mnodes_between.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:16:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/19 15:42:06 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

int	ft_insert_mnode_between(t_mmlst *mmlst, t_mnode *mnode, t_mmlst *new_mmlst)
{
	t_mnode		*temp;

	if (!mmlst || !mnode || !new_mmlst)
		return (-1);
	if (mmlst->size == 0 || new_mmlst->size == 0)
		return (-1);
	if (mmlst->size == 1)
	{
		mnode->next = new_mmlst->head;
		new_mmlst->head->prev = mnode;
		mnode->prev = new_mmlst->last;
		new_mmlst->last->next = mnode;
		mmlst->last = new_mmlst->last;
		mmlst->size += new_mmlst->size;	
	}
	else if (mmlst->head == mnode)
	{
		temp = mnode->next;
		mmlst->head->next = new_mmlst->head;
		temp->prev = new_mmlst->last;
		new_mmlst->head->prev = mmlst->head;
		new_mmlst->last->next = temp;
		mmlst->size += new_mmlst->size;
	}
	else if (mmlst->last == mnode)
	{
		temp = mmlst->last->prev;
		temp->next = new_mmlst->head;
		new_mmlst->head->prev = temp;
		new_mmlst->last->next = mmlst->last;
		mmlst->last->prev = new_mmlst->last;
		mmlst->size += new_mmlst->size;
	}
	else
	{
		temp = mnode->next;
		mnode->next = new_mmlst->head;
		new_mmlst->head->prev = mnode;
		temp->prev = new_mmlst->last;
		new_mmlst->last->next = temp;
		mmlst->size += new_mmlst->size;
	}
	return (0);
}
