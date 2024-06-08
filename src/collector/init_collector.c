/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_collector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:07:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/08 14:45:20 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"

t_collector *ft_init_collector(void)
{
	t_collector	*collector;

	collector = malloc(sizeof(t_collector));
	if (!collector)
		return (NULL);
	collector->head = NULL;
	collector->last = NULL;
	collector->size = 0;
	return (collector);
}

t_void *ft_initt_void(void)
{
	t_void	*col;

	col = malloc(sizeof(t_void));
	if (!col)
		return (NULL);
	col->head = NULL;
	col->last = NULL;
	col->size = 0;
	return (col);
}