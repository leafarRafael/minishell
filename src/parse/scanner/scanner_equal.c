/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_equal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:25:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:57:18 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	ft_scanner_equal(t_lst *lst)
{
	t_node	*node;
	int		i;

	i = 1;
	node = lst->head;
	while (i <= lst->size)
	{
		if (node->c == '=')
			node->type = EQUAL_SING;
		else
			node->type = NO_OP_TYPE;
		node = node->next;
		i++;
	}
}
