/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:39:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 10:55:50 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

int	ft_delete_list(t_lst *lst)
{
	if (!lst)
		return (-1);
	while (lst->size > 0)
		ft_remove_node_front(lst);
	free(lst);
	lst = NULL;
	return (0);
}
