/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:05:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/24 07:37:30 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "minishell.h"

char	**ft_init_color()
{
	char	**mtrix_color;

	mtrix_color = (ft_calloc(sizeof(char *), 8));
	if (!mtrix_color)
		return (NULL);
	mtrix_color[0] = ft_strdup("\033[31m");
	mtrix_color[1] = ft_strdup("\033[32m");
	mtrix_color[2] = ft_strdup("\033[33m");
	mtrix_color[3] = ft_strdup("\033[34m");
	mtrix_color[4] = ft_strdup("\033[35m");
	mtrix_color[5] = ft_strdup("\033[36m");
	mtrix_color[6] = ft_strdup("\033[37m");
	mtrix_color[7] = NULL;
	return (mtrix_color);
}