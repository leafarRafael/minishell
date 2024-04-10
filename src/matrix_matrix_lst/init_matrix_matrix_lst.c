/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix_matrix_lst.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:50:36 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/10 14:43:27 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

t_mtrx_mtrx	*ft_mtrx_mtrx_lst(void)
{
	t_mtrx_mtrx	*mtrx_lst;

	mtrx_lst = malloc(sizeof(t_mtrx_mtrx));
	mtrx_lst->head = NULL;
	mtrx_lst->last = NULL;
	mtrx_lst->size = 0;
	return (mtrx_lst);
}