/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:21:26 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/08 12:07:10 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_executable(char *command, char **path)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	if (access(command, X_OK | F_OK) == 0)
		return (ft_strdup(command));
	temp = NULL;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		temp2 = ft_strjoin(temp, command);
		free(temp);
		temp = NULL;
		if (access(temp2, X_OK | F_OK) == 0)
			return (temp2);
		free(temp2);
		temp2 = NULL;
		i++;
	}
	return (NULL);
}
