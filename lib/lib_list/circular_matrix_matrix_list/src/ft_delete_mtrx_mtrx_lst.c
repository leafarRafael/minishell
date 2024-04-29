/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_mtrx_mtrx_lst.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:27:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 11:30:25 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

int	ft_delete_mtrx_mtrx_lst(t_mtrx_mtrx *m_matrix)
{
	if (!m_matrix)
		return (-1);
	while (m_matrix->size > 0)
		ft_remove_matrix_back(m_matrix);
	free(m_matrix);
	m_matrix = NULL;
	return (0);
}
