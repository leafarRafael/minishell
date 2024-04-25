/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/25 09:22:52 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_simple_cmd(t_var_minishell *mini)
{
	t_var_exe	var;

	var.pid = fork();
	if (var.pid == 0)
	{
		var.command_m = ft_cpy_mtrllst_to_cmtrx(mini->list_matrix->head->matrix);
		var.env = ft_path_env(mini->mrtx_lst_env);
		var.path_exe = ft_get_executable(var.command_m[0], var.env);
		execve(var.path_exe, var.command_m, var.env);
	}
}

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