/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:21:26 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 09:21:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*ft_get_executable(char *command, char **path)
{
	int		i;
	char	*temp;

	i = 0;
	if (access(command, X_OK | F_OK) == 0)
		return (ft_strdup(command));
	temp = NULL;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		temp = ft_strjoin(temp, command);
		if (access(temp, X_OK | F_OK) == 0)
			return (temp);
		free(temp);
		temp = NULL;
		i++;
	}
	return (NULL);
}