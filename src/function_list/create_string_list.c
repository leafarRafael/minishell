/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_string_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 08:49:47 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/28 08:28:26 by rbutzke          ###   ########.fr       */
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
			ft_putstr_fd("error creation array_list", STDERR_FILENO);
			return (-1);
		}
		i++;
	}
	return (0);
}