/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_mmlst.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:27:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 07:58:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

int	ft_delete_mmlst(t_mmlst *m_matrix)
{
	if (!m_matrix)
		return (-1);
	while (m_matrix->size > 0)
		ft_remove_matrix_front(m_matrix);
	free(m_matrix);
	m_matrix = NULL;
	return (0);
}
