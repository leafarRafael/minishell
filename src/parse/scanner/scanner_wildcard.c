/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:38:27 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/23 16:44:47 by rbutzke          ###   ########.fr       */
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
		node = node->next;
		i++;
	}
}