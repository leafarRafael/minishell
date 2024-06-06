/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_mlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:49:24 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/06 10:36:57 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

static t_llst	*find_less(t_mlst *mlst);

t_mlst	*ft_bubble_sort(t_mlst *mlst)
{
	t_llst	*node_a;
	t_llst	*new_n;
	t_mlst	*sort;

	add_lexicographic_value(mlst, '\0');
	sort = init_mlst();
	while (1)
	{
		if (mlst->size == 0)
			break ;
		node_a = find_less(mlst);
		if (node_a == NULL)
			break ;
		new_n = mlst_rmv_return_lnode(mlst, node_a);
		ft_add_mlstnode_back(sort, new_n);
	}
	free(mlst);
	return (sort);
}

static t_llst	*find_less(t_mlst *mlst)
{
	t_llst	*llst;
	t_llst	*less;

	if (mlst->size == 0)
		return (NULL);
	if (mlst->size == 1)
		return (mlst->head);
	llst = mlst->head;
	less = mlst->head;
	while (llst->next != mlst->head)
	{
		if (llst->lex_val < less->lex_val)
			less = llst;
		llst = llst->next;
	}
	return (less);
}
