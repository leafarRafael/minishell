/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_array_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:06:17 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/22 09:27:45 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

t_array_lst	*init_array_lst(void)
{
	t_array_lst	*array_lst;

	array_lst = malloc(sizeof(t_array_lst));
	if (!array_lst)
		return (NULL);
	array_lst->head = NULL;
	array_lst->last = NULL;
	array_lst->size = 0;
	return (array_lst);
}
