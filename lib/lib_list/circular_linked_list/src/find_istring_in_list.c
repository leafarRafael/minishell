/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_istring_in_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:46:09 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/26 09:14:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

int	ft_find_str_inlist(t_lst *lst, char *str, int size)
{
	t_var	v;
	int		index;

	v.i = 1;
	index = 0;
	v.temp_node = lst->head;
	while (v.i <= lst->size && v.i <= size)
	{
		if (str[index] == v.temp_node->c)
			index++;
		else
			index = 0;
		if (index == size)
			break;
		v.temp_node = v.temp_node->next;
		v.i++;
	}
	if (index == size)
		return (index);
	return (-1);
}