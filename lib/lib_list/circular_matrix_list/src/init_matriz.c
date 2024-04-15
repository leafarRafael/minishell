/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matriz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:18:07 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/10 14:43:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

t_mtrx_lst	*ft_init_matrix(void)
{
	t_mtrx_lst	*matrix;

	matrix = malloc(sizeof(t_mtrx_lst));
	if (!matrix)
		return (NULL);
	matrix->head = NULL;
	matrix->last = NULL;
	matrix->size = 0;
	return (matrix);
}