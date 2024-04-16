/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_cmtrx_to_mtrx_lst.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:54:19 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/16 15:54:37 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lst.h"

t_mtrx_lst	*ft_cmtrix_to_mtrx_lst(char **matrix)
{
	t_mtrx_lst	*new_mtrx_lst;
	t_lst		*new_lst;
	int			i;

	if (!matrix)
		return (NULL);
	new_mtrx_lst = ft_init_matrix();
	i = 0;
	while (matrix[i])
	{
		new_lst = ft_init_lst();
		ft_add_string_in_list(new_lst, matrix[i]);
		ft_add_list_back(new_mtrx_lst, new_lst);
		i++;
	}
	return (new_mtrx_lst);
}