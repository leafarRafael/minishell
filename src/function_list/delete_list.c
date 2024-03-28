/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:39:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/28 08:25:32 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

int	ft_delete_list(t_lst *lst)
{
	t_var	var;

	if (!lst)
		return (-1);
	if (!lst->head && !lst->last)
		return (-1);
	while (lst->size != 0)
		ft_remove_node_front(lst);
	free(lst);
	return (0);	
}