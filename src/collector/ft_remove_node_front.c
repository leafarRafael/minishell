/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_node_front.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:44:37 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 14:35:54 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"

static int	ft_one_node(t_clct *collec);
static int	ft_two_node(t_clct *collec);
static int	ft_three_more(t_clct *collec);

int	cllctr_rmv_front(t_clct *collec)
{
	if (!collec)
		return (1);
	if (collec->size == 0)
		return (1);
	if (collec->size == 1)
		return (ft_one_node(collec));
	if (collec->size == 2)
		return (ft_two_node(collec));
	return (ft_three_more(collec));
}

static int	ft_one_node(t_clct *collec)
{
	free(collec->head);
	collec->size = 0;
	collec->head = NULL;
	collec->last = NULL;
	return (0);
}

static int	ft_two_node(t_clct *collec)
{
	free(collec->head);
	collec->last->prev = collec->last;
	collec->last->next = collec->last;
	collec->head = collec->last;
	collec->size--;
	return (0);
}

static int	ft_three_more(t_clct *collec)
{
	collec->head->next->prev = collec->last;
	collec->last->next = collec->head->next;
	free(collec->head);
	collec->head = collec->last->next;
	collec->size--;
	return (0);
}
