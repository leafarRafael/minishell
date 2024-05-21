/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_after_expanding.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:20:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/21 14:30:27 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	ft_scanner_after_expand(t_lst *lst)
{
	t_node	*node;
	int		i;

	i = 1;
	node = lst->head;
	while(i <= lst->size)
	{
		if (node->c == ' ')
			node->type = WH_SPACE;
		else
			node->type = NO_OP_TYPE;
		node = node->next;
		i++;
	}
}
