/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_node_mmlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:05:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/11 16:00:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

static t_mnode	*ft_size_one(t_mmlst *mm_lst, t_mnode *mnode);

t_mnode	*ft_pop_mnode(t_mmlst *mm_lst, t_mnode *mnode)
{
	t_var_m_mlst	v;

	if (!mm_lst || !mnode)
		return (NULL);
	if (mm_lst->size == 0)
		return (NULL);
	if (mnode->next == mnode)
		return (ft_size_one(mm_lst, mnode));
	v.next = mnode->next;
	v.prev = mnode->prev;
	v.prev->next = v.next;
	v.next->prev = v.prev;
	if (mnode == mm_lst->head)
		mm_lst->head = v.next;
	if (mnode == mm_lst->last)
		mm_lst->last = v.prev;
	mnode->next = NULL;
	mnode->prev = NULL;
	mm_lst->size--;
	return (mnode);
}

static t_mnode	*ft_size_one(t_mmlst *mm_lst, t_mnode *mnode)
{
	mm_lst->head = NULL;
	mm_lst->last = NULL;
	mm_lst->size--;
	mnode->next = NULL;
	mnode->prev = NULL;
	return (mnode);
}
