/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_collector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:39:38 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/08 18:59:51 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"

int	ft_delete_collector(t_collector *collec, void (del_content)(t_ast *))
{
	if (!collec)
		return (0);
	if (collec->size == 0)
	{
		free(collec);
		return (0);
	}
	while (collec->size)
	{
		if (del_content)
			del_content(collec->head->type.ast);
		collector_rmv_front(collec);
	}
	free(collec);
	collec = NULL;
	return (0);
}
