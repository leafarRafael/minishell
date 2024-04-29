/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:18:07 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 10:09:10 by rbutzke          ###   ########.fr       */
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