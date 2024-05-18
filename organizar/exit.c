/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:37 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/17 15:45:55 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *input)
{
	int	i;

	if (!input)
		return (-1);
	i = 0;
	while (ft_words_delemiter(input[i]))
		i++;
	if (ft_strncmp("exit", &input[i], 4) == 0)
	{
		free(input);
		input = NULL;
		return (0);
	}
	return (-1);
}
