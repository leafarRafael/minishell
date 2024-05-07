/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:09:29 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 08:29:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

int	ft_delete_matrix(t_mlst *matrix)
{
	if (!matrix)
		return (-1);
	if (matrix->size == 0)
		return (-1);
	if (matrix->size > 0)
	{
		while (matrix->size > 0)
			ft_remove_list_back(matrix);
		free(matrix);
		matrix = NULL;
		return (0);
	}
	return (-1);
}
