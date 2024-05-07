/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_mtrllst_to_cmtrx.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:18:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 08:29:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

char	**ft_cpy_mtrllst_to_cmtrx(t_mlst *lst_matrix)
{
	t_var_matrix	v;

	v.matrix = NULL;
	if (!lst_matrix)
		return (v.matrix);
	v.matrix = malloc(sizeof(char *) * (lst_matrix->size +1));
	if (!v.matrix)
		return (v.matrix);
	v.current_lst = lst_matrix->head;
	v.index = 0;
	v.i = 1;
	while (v.i <= lst_matrix->size)
	{
		if (v.current_lst->lst->size != 0)
		{
			v.matrix[v.index] = ft_cpy_lst_to_array(v.current_lst->lst);
			v.index++;
		}
		v.current_lst = v.current_lst->next;
		v.i++;
	}
	v.matrix[v.i -1] = NULL;
	return (v.matrix);
}
