/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:21:02 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 16:45:43 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

static void	ft_is_quotes(int *i);

void	ft_scanner_quotes(t_lst *lst)
{
	t_scan	v;

	v.i = 0;
	v.d_quotes = 0;
	v.s_quotes = 0;
	v.node = lst->head;
	while (v.i <= lst->size)
	{
		if (v.node->type == D_QUOTES && v.s_quotes == 0)
			ft_is_quotes(&v.d_quotes);
		if (v.node->type == S_QUOTES && v.d_quotes == 0)
			ft_is_quotes(&v.s_quotes);
		if (v.s_quotes == 1 && v.node->type != S_QUOTES)
			v.node->type = NO_OP_TYPE;
		if (v.d_quotes == 1
			&& v.node->type != D_QUOTES && v.node->type != DOLLAR)
		{
			if (v.node->type != NO_OP_TYPE)
				v.node->type = META_LITERAL;
		}
		v.node = v.node->next;
		v.i++;
	}
}

static void	ft_is_quotes(int *i)
{
	if ((*i) == 1)
		(*i)--;
	else
		(*i)++;
}
