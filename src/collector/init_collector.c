/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_collector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:07:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/08 16:25:23 by rbutzke          ###   ########.fr       */
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
