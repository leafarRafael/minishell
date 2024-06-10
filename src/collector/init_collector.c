/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_collector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:07:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 14:34:19 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"

t_clct	*ft_init_collector(void)
{
	t_clct	*collector;

	collector = malloc(sizeof(t_clct));
	if (!collector)
		return (NULL);
	collector->head = NULL;
	collector->last = NULL;
	collector->size = 0;
	return (collector);
}
