/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:21:26 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 12:13:30 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *binary_with_path(char *path_bin, t_mini *mini, t_var_exe *var, t_ast *ast);

char	*ft_get_executable(t_mini *mini, t_var_exe *var, t_ast *ast)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	temp = binary_with_path(var->command_m[0], mini, var, ast);
	if (temp != 0)
		return (temp);
	temp = NULL;
	while (var->env[i])
	{
		temp = ft_strjoin(var->env[i], "/");
		temp2 = ft_strjoin(temp, var->command_m[0]);
		free(temp);
		temp = NULL;
		if (access(temp2, X_OK | F_OK) == 0)
			return (temp2);
		free(temp2);
		temp2 = NULL;
		i++;
	}
	ft_msg_error(var->command_m[0], "command not found");
	free_memory(mini, var, 127);
	return (NULL);
}

static char *binary_with_path(char *path_bin, t_mini *mini, t_var_exe *var, t_ast *ast)
{
	int	fd;

	if (ft_strchr(path_bin, '/') != NULL)
	{
		fd = open(path_bin, __O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			ft_msg_error(path_bin, " Is a directory");
			free_memory(mini, var, 126);
		}
		if ((access(path_bin, X_OK) == 0))
			return (ft_strdup(path_bin));
		else
		{
			if (errno == EACCES)
			{
				ft_msg_error(path_bin, strerror(errno));
				free_memory(mini, var, 126);
			}
			ft_msg_error(path_bin, strerror(errno));
			free_memory(mini, var, 127);
		}
	}
	return (NULL);
}