/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_mnodes_between.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:16:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/18 18:44:47 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

int	*ft_insert_mnode_between(t_mmlst *mmlst, t_mnode *pointer, t_mlst *content)
{
	t_mnode *next;
	t_mnode *prev;
	t_mnode	*new_node;

	new_node = initinit_matrix_node();
	new_node->matrix = content;
	if (!mmlst)
		return (-1);
	if(!pointer)
		return (-1);
	if (!new_node)
		return (-1);
	if (mmlst->size == 0)
	{
		ft_mmlst_add_front(mmlst, new_node);
		return (new_node);
	}
	if (pointer == mmlst->head)
		ft_add_node_front(mmlst, new_node);
	else if (pointer == mmlst->last)
		ft_add_node_back(mmlst, new_node);
	else
	{
		next = pointer->next;
		prev = pointer->prev;
		new_node->next = next;
		next->prev = new_node;
		new_node->prev = prev;
		prev->next = new_node;
	}
	return (0);
}
