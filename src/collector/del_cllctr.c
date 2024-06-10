/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_cllctr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:39:38 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 14:38:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"

int	del_cllctr(t_clct *collec, void (del_content)(t_ast *))
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
		cllctr_rmv_front(collec);
	}
	free(collec);
	collec = NULL;
	return (0);
}
