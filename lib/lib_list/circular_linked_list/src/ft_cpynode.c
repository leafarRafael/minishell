/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpynode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:38:33 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/24 15:37:54 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

t_node	*ft_cpynode(t_node *node_origin)
{
	t_node	*new_node;

	if (!node_origin)
		return (NULL);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->c = node_origin->c;
	new_node->type = node_origin->type;
	new_node->paren = node_origin->paren;
	new_node->priority = node_origin->priority;
	new_node->lex_val = node_origin->lex_val;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
