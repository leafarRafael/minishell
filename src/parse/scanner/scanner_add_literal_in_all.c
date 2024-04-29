/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_add_literal_in_all.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:14:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 16:42:06 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

int	ft_scanner_add_literal(t_lst *lst)
{
	t_scan	v;

	if (!lst)
		return (-1);
	if (lst->size == 0)
		return (-1);
	v.i = 1;
	v.node = lst->head;
	while (v.i <= lst->size)
	{
		v.node->type = NO_OP_TYPE;
		v.node = v.node->next;
		v.i++;
	}
	return (0);
}
