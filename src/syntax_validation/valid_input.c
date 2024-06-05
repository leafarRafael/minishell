/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:27:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/05 17:36:22 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_syntax.h"


int	ft_input_is_valid(char *array)
{
	int i;
	int size;

	i = 0;
	size = 0;
	size = ft_strlen(array);

	if (size == 0)
		return (-1);
	add_history(array);
	while (array[i])
	{
		if (!ft_words_delemiter(array[i]))
			return (th_parse_param(array));
		i++;
	}
	return (1);
}
