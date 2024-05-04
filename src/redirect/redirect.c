/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:23:10 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/04 17:00:27 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

void	ft_redirect(t_mtrx_lst *mtrix)
{
	t_redirect	var;

	var.index = 1;
	var.node_c = mtrix->head;
	var.node_n = var.node_c->next;
	var.size = mtrix->size;
	while (var.index <= var.size)
	{
		if (var.node_c->rdrct == HERE_DOC)
			ft_open_here_doc(mtrix, var.node_c);
		if (var.node_c->rdrct == REDI_IN)
			ft_open_infile(mtrix, var.node_c);
		if (var.node_c->rdrct == APPEND)
			ft_open_append(mtrix, var.node_c);
		if (var.node_c->rdrct == REDI_OUT)
			ft_opens_truncate(mtrix, var.node_c);
		var.index++;
		var.node_c = var.node_n;
		var.node_n = var.node_n->next;
	}
}