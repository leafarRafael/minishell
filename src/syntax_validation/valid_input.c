/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:27:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/06 18:01:45 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_syntax.h"


int	ft_input_is_valid(char *array)
{
	int	i;
	int	size;
	int	status;

	status = 1;
	i = 0;
	size = ft_strlen(array);
	if (size == 0)
	{
		g_status_child = 0;
		return (1);
	}
	add_history(array);
	while (array[i] && ft_words_delemiter(array[i]))
	{
		i++;
		if (array[i] == '\0')
		{
			g_status_child = 0;
			return (1);
		}
	}
	status = th_parse_param(array);
	if (status)
		g_status_child = 1;
	return (status);
}
