/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_simple_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:26:32 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 16:46:24 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	ft_scanner_simple_operator(t_lst *lst)
{
	t_scan	v;

	v.i = 0;
	v.node = lst->head;
	while (v.i <= lst->size)
	{
		v.node->type = is_simple_type(v.node->c);
		v.node = v.node->next;
		v.i++;
	}
}
