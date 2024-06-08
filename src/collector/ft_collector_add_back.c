/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collector_add_back.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:17:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/08 18:46:10 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"

static int	case_zero(t_collector *collec, t_ncollec *node);
static int	case_one(t_collector *collec,  t_ncollec *node);
static int	case_others(t_collector *collec, t_ncollec *node);

int	collector_add_back(t_collector *collec, void *cont, void *(*ft_func)(void *))
{
	void	*node;

	if (!collec)
		return (1);
	node = ft_func(cont);
	if (collec->size == 0)
		return (case_zero(collec, node));
	if (collec->size == 1)
		return (case_one(collec, node));
	return (case_others(collec, node));
}

static int	case_zero(t_collector *collec, t_ncollec *node)
{
	node->next = node;
	node->prev = node;
	collec->head = node;
	collec->last = node;
	collec->size++;
	return (0);
}

static int	case_one(t_collector *collec, t_ncollec *node)
{
	node->prev = collec->head;
	node->next = collec->head;
	collec->head->prev = node;
	collec->head->next = node;
	collec->last = node;
	collec->size++;
	return (0);
}

static int	case_others(t_collector *collec, t_ncollec *node)
{
	node->prev = collec->last;
	node->next = collec->head;
	collec->head->prev = node;
	collec->last->next = node;
	collec->last = node;
	collec->size++;
	return (0);
}
