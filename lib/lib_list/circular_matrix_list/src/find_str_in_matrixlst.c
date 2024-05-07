/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_str_in_matrixlst.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:45:10 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 08:29:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

t_lst	*find_str_in_matrixlst(t_mlst *m_lst, char *str, int size)
{
	t_var_matrix	v;

	v.current_lst = m_lst->head;
	v.i = 1;
	while (v.i <= m_lst->size)
	{
		if (ft_find_str_inlist(v.current_lst->lst, str, size) == size)
			return (v.current_lst->lst);
		v.i++;
		v.current_lst = v.current_lst->next;
	}
	return (NULL);
}
