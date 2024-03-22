/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix_array_lst.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:36:32 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/22 16:30:24 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

t_matrix_lst	*ft_init_matrix_lst(void)
{
	t_matrix_lst	*matrix_lst;

	matrix_lst = malloc(sizeof(t_matrix_lst));
	if (!matrix_lst)
		return (NULL);
	matrix_lst->head_line = NULL;
	matrix_lst->last_line = NULL;
	matrix_lst->next_line = NULL;
	matrix_lst->prev_line = NULL;
	matrix_lst->size = 0;
	return (matrix_lst);
}
