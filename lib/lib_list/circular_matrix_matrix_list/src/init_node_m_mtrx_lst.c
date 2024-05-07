/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node_m_mtrx_lst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:53:40 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/07 15:36:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_matrix_lst.h"

t_mnode	*init_matrix_node(void)
{
	t_mnode	*new_matrix_node;

	new_matrix_node = malloc(sizeof(t_mnode));
	new_matrix_node->matrix = NULL;
	new_matrix_node->type = -42;
	new_matrix_node->in_tree = -42;
	new_matrix_node->next = NULL;
	new_matrix_node->prev = NULL;
	return (new_matrix_node);
}
