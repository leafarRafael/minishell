/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_parenthes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:23:47 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/08 11:25:18 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"
#include <stdio.h>

static void	ft_close_open_parant(char c, int *ctrl_parent, int *parenth);

void	ft_scanner_parenthes(t_lst *lst)
{
	t_scan	v;

	v.i = 1;
	v.parentheses = 0;
	v.node = lst->head;
	while (v.i <= lst->size)
	{
		if (v.node->type & (OPEN_PAREN | CLOSE_PAREN))
			ft_close_open_parant(v.node->c, &v.parentheses, &v.node->paren);
		v.node = v.node->next;
		v.i++;
	}
}

static void	ft_close_open_parant(char c, int *ctrl_parent, int *parenth)
{
	if (ft_open_parent(c))
	{
		(*ctrl_parent)++;
		(*parenth) = (*ctrl_parent);
	}
	else if (ft_close_parent(c))
	{
		(*parenth) = (*ctrl_parent);
		(*ctrl_parent)--;
	}
	else
		(*parenth) = -1;
}
