/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_string_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 08:49:47 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/15 09:24:27 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

int	ft_add_string_in_list(t_lst *lst, char *array)
{
	int	i;

	if (!lst || !array)
	 	return (-1);
	i = 0;
	while (array[i])
	{
		if (ft_create_node_add_back(lst, array[i]))
		{
			write(STDERR_FILENO, "error creation array_list\n", 29);
			return (-1);
		}
		i++;
	}
	return (0);
}