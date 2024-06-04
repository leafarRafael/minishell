/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:44:46 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:49:48 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

void	ft_remove_quotes_lst(t_lst *lst)
{
	t_node	*node;
	t_node	*next;
	int		counter;

	node = lst->head;
	next = node->next;
	counter = 1;
	while (counter <= lst->size)
	{
		if (node->type & (D_QUOTES | S_QUOTES))
		{
			ft_remove_specific_node(lst, node);
			counter--;
		}
		node = next;
		if (lst->size == 0)
			break ;
		next = next->next;
		counter++;
	}
}
