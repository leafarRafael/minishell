/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matriz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:18:07 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/27 17:32:38 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

t_matrix	*ft_init_matrix(void)
{
	t_matrix	*matrix;

	matrix = malloc(sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	matrix->next = NULL;
	matrix->prev = NULL;
	matrix->size = 0;
	return (matrix);
}