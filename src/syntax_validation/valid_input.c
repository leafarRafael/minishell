/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:27:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/09 15:50:23 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_syntax.h"

int	ft_input_is_valid(char *array)
{
	t_stx	v;

	v.status = 1;
	v.i = 0;
	v.size = ft_strlen(array);
	if (v.size == 0)
	{
		g_status_child = 0;
		return (1);
	}
	add_history(array);
	while (array[v.i] && ft_words_delemiter(array[v.i]))
	{
		v.i++;
		if (array[v.i] == '\0')
		{
			g_status_child = 0;
			return (1);
		}
	}
	v.status = th_parse_param(array);
	if (v.status)
		g_status_child = 1;
	return (v.status);
}
