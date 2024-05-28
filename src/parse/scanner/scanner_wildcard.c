/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:38:27 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/28 13:39:00 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	ft_scanner_wildcard(t_lst *lst)
{
	t_node	*node;
	int		i;

	i = 1;
	node = lst->head;
	while(i <= lst->size)
	{
		if (whildcard(node->c))
			node->type = WILDCARD;
		if (node->c == '=')
			node->type = EQUAL_SING;
		node = node->next;
		i++;
	}
}