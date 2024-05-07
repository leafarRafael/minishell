/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix_matrix_lst.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:50:36 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 07:58:55 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

t_mmlst	*init_mmlst(void)
{
	t_mmlst	*mtrx_lst;

	mtrx_lst = malloc(sizeof(t_mmlst));
	mtrx_lst->head = NULL;
	mtrx_lst->last = NULL;
	mtrx_lst->size = 0;
	return (mtrx_lst);
}
