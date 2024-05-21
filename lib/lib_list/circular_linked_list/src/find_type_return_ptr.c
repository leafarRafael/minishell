/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_type_return_ptr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:59:03 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/21 13:03:14 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

t_node	*find_type_return_ptr(t_lst *lst, int type)
{
	int		i;
	t_node	*node;

	if (!lst)
		return (NULL);
	if (lst->size == 0)
		return (NULL);
	i = 1;
	node = lst->head;
	while (i <= lst->size)
	{
		if (node->type == type)
			return (node);
		i++;
		node = node->next;
	}
	return (NULL);
}