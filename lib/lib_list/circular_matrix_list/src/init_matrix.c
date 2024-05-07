/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:18:07 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 08:29:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

t_mlst	*ft_init_matrix(void)
{
	t_mlst	*matrix;

	matrix = malloc(sizeof(t_mlst));
	if (!matrix)
		return (NULL);
	matrix->head = NULL;
	matrix->last = NULL;
	matrix->size = 0;
	return (matrix);
}
