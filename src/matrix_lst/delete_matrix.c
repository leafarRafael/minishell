/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:09:29 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/11 09:40:55 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

int	ft_delete_matrix(t_mtrx_lst *matrix)
{
	if (!matrix)
		return (-1);
	if (matrix->size == 0)
	{
		free(matrix);
		matrix = NULL;
		return (0);
	}
	else if (matrix->size == 1)
	{
		ft_remove_lst_front(matrix);
		free(matrix->head);
		free(matrix);
		matrix = NULL;
		return (0);
	}
	else if (matrix->size > 1)
	{
		while (matrix->size > 0)
			ft_remove_lst_front(matrix);
		free(matrix->head);
		free(matrix);
		matrix = NULL;
		return (0);
	}
	return (0);	
}