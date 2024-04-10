/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_for_priotity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:25:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/09 15:00:51 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

static int value_priority(int type);

void	ft_scanner_priority_type(t_lst *lst)
{
	t_scan	v;

	v.i = 1;
	v.node = lst->head;
	while (v.i <= lst->size )
	{
		v.node->priority = value_priority(v.node->type);
		v.node = v.node->next;
		v.i++;
	}
}

static int value_priority(int type)
{
	if (type & (OPEN_PAREN | CLOSE_PAREN))
		return (HIGH);
	if (type & (REDI_IN | REDIRECT | APPEND | HERE_DOC))
		return (MEDIUM);
	if (type == PIPE)
		return (LOWEST);
	if (type & (AND_OP | OR_OP))
		return (LOWEST);
	return (-1);
}