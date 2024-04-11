/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_mtrllst_to_cmtrx.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:18:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/11 14:24:35 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"
#include "expanding.h"

char	**ft_cpy_mtrllst_to_cmtrx(t_mtrx_lst *lst_matrix)
{
	t_var_matrix	v;

	if (!lst_matrix)
		return (NULL);
	v.matrix = ft_calloc(sizeof(char*), lst_matrix->size +1);
	v.current_lst = lst_matrix->head;
	v.i = 1;
	v.index = 0;
	while (v.i <= lst_matrix->size)
	{
		ft_expander_lst_token(v.current_lst->lst);
		v.matrix[v.index] = ft_cpy_lst_to_array(v.current_lst->lst);
		v.current_lst = v.current_lst->next;
		v.i++;
		v.index++;
	}
	return (v.matrix);
}