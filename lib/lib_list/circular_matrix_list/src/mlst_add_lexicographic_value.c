/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlst_add_lexicographic_value.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/06 13:47:18 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

/* static int	ft_find_the_smallest_size(t_mlst *mlst); */

static int	ft_find_the_smallest_size(t_mlst *mlst, char limiter);

int	add_lexicographic_value(t_mlst *mlst, char limiter)
{
	t_var_matrix	v;

	v.i_m = 0;
	v.current_lst = mlst->head;
	v.size = ft_find_the_smallest_size(mlst, limiter);
	while (v.i_m < mlst->size)
	{
		v.i_l = 0;
		v.node = v.current_lst->lst->head;
		v.current_lst->lex_val = 0;
		while (v.i_l < v.size || v.i_l < v.current_lst->lst->size)
		{
			v.current_lst->lex_val += v.node->lex_val;
			v.node = v.node->next;
			v.i_l++;
			if (v.node->c == limiter)
				break ;
		}
		v.i_m ++;
		v.current_lst = v.current_lst->next;
	}
	return (0);
}

static int	ft_find_the_smallest_size(t_mlst *mlst, char limiter)
{
	t_llst	*lnode;
	t_node	*node;
	int		i;
	int		x;
	int		size;

	i = 0;
	size = __INT_MAX__;
	lnode = mlst->head;
	while (i < mlst->size)
	{
		x = 0;
		node = lnode->lst->head;
		while (x < lnode->lst->size)
		{
			if (node->c == limiter)
			{
				x--;
				break ;
			}
			node = node->next;
			x++;
		}
		if (x < size)
			size = x;
		lnode = lnode->next;
		i++;
	}
	return (size);
}
