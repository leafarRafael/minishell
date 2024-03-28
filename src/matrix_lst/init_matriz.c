/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matriz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:18:07 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/28 08:57:23 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

t_matrix_lst	*ft_init_matrix(void)
{
	t_matrix_lst	*matrix;

	matrix = malloc(sizeof(t_matrix_lst));
	if (!matrix)
		return (NULL);
	matrix->head = NULL;
	matrix->last = NULL;
	matrix->size = 0;
	return (matrix);
}