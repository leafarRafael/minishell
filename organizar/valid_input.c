/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:27:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 17:08:35 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_input_is_valid(char *array)
{
	int i;
	int size;

	i = 0;
	size = 0;
	if (!array)
		return (-1);
	size = ft_strlen(array);
	if (size == 0)
	{
		free(array);
		return (-1);
	}
	if (size == 1)
	{
		if (ft_words_delemiter(array[0]))
		{
			free(array);
			return (-1);
		}
		write(2, array, size);
		write(2, ": command not found\n", 21);
		free(array);
		return (-1);
	}
	while (array[i])
	{
		if (!ft_words_delemiter(array[i]))
			return (0);
		i++;
	}
	free(array);
	return (-1);
}