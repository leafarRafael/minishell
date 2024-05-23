/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pathname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:55:33 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/23 18:31:15 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

void	ft_put_program_name()
{
	char	**path_name;
	char	**color;
	char	*directory;
	int		i;
	int		i_color;

	i = 0;
	i_color = 0;
	color = ft_init_color();
	directory = (char *) getdir_list_string(STRING);
	path_name = ft_split(directory, '/');
	while (path_name[i])
	{
		printf("%s%s%s", color[i_color], path_name[i], RESET);
		printf("%s/%s", color[i_color], RESET);
		if (i_color == 7)
			i_color = 0;
		i_color++;
		i++;
	}
	ft_delcmtrx(color);
	ft_delcmtrx(path_name);
	free(directory);
}