/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_composite_op.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:27:49 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/09 15:01:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	ft_scanner_composite(t_lst *lst)
{
	t_scan	v;

	v.i = 1;
	v.node = lst->head;
	while (v.i <= lst->size )
	{
		v.type = -1;
		v.type = ft_is_composite_type(v.node->c, v.node->next->c);
		if (v.type != -1 && v.node != lst->last)
		{
			v.node->type = v.type;
			v.node->next->type = v.type;
			v.node = v.node->next;
			v.i++;
		}
		v.node = v.node->next;
		v.i++;
	}
}