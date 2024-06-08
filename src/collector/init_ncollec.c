/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncollec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:13:31 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/08 11:20:25 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"

t_ncollec	*ft_init_ncollec(void)
{
	t_ncollec *node;

	node = malloc(sizeof(t_ncollec));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	node->pid = -42;
	return (node);
}