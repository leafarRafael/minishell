/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:39:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/13 13:12:31 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

int	ft_delete_list(t_lst *lst)
{
	t_var	var;

	if (!lst)
		return (-1);
	if (lst->size == 0 && lst->head != NULL)
	{
		free(lst);
		lst = NULL;
		return (0);
	}
	while (lst->size > 0)
		ft_remove_node_front(lst);
	free(lst);
	lst = NULL;
	return (0);	
}