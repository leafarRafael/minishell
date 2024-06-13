/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlst_add_lexicographic_value.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/13 08:51:58 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"
#include <stdio.h>

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
		while (v.i_l < v.size && v.i_l < v.current_lst->lst->size)
		{
			v.current_lst->lex_val += v.node->lex_val;
			v.node = v.node->next;
			v.i_l++;
			if (v.i_l == v.size)
				break ;
		}
		v.i_m ++;
		v.current_lst = v.current_lst->next;
	}
	return (0);
}

static int	ft_find_the_smallest_size(t_mlst *mlst, char limiter)
{
	t_var_matrix	v;

	v.i_m = 0;
	v.size = __INT_MAX__;
	v.current_lst = mlst->head;
	while (v.i_m < mlst->size)
	{
		v.i_l = 0;
		v.node = v.current_lst->lst->head;
		while (v.i_l < v.current_lst->lst->size)
		{
			if (v.node->c == limiter)
				break ;
			v.node = v.node->next;
			v.i_l++;
		}
		v.size = v.i_l;
		v.current_lst = v.current_lst->next;
		v.i_m++;
	}
	return (v.size);
}
