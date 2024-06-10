/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncollec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:13:31 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 14:35:35 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"

void	*node_collect_pid(void *content)
{
	t_ncllc	*node;

	node = malloc(sizeof(t_ncllc));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	node->status = 0;
	node->type.pid = *((pid_t *)content);
	return (node);
}

void	*node_collect_ast(void *content)
{
	t_ncllc	*node;

	node = malloc(sizeof(t_ncllc));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	node->status = 0;
	node->type.ast = (t_ast *)content;
	return (node);
}
