/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_mlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:49:24 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/25 11:53:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

t_llst	*find_less(t_mlst *mlst);
int	add_lexicographic_value(t_mlst *mlst, char limiter);
int	ft_find_the_smallest_size(t_mlst *mlst);

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
		new_n = ft_remove_return_mlst_node(mlst, node_a);
		ft_add_mlstnode_back(sort, new_n);
	}
	free(mlst);
	return (sort);
}

t_llst	*find_less(t_mlst *mlst)
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

int	add_lexicographic_value(t_mlst *mlst, char limiter)
{
	t_node	*node;
	t_llst	*lnode;
	int		i_m;
	int		i_l;
	int 	size;

	i_m = 1;
	lnode = mlst->head;
	size = ft_find_the_smallest_size(mlst);
	while (i_m <= mlst->size)
	{
		i_l = 0;
		node = lnode->lst->head;
		lnode->lex_val = 0;
		while (i_l < size && i_l < lnode->lst->size)
		{
			lnode->lex_val += node->lex_val;
			i_l++;
			node = node->next;
			if (node->c == limiter)
				break ;
		}
		i_m++;
		lnode = lnode->next;
	}
	return (0);
}

int	ft_find_the_smallest_size(t_mlst *mlst)
{
	t_llst	*lnode;
	int		size;

	lnode = mlst->head;
	size = 0;
	while (lnode->next != mlst->head)
	{
		if (lnode->lst->size < size)
			size = lnode->lst->size;
		lnode = lnode->next;
	}
	return (size);
}
