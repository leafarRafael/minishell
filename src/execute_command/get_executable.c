/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:21:26 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/17 16:39:32 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_executable(t_mini *mini, t_var_exe *var, t_ast *ast)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	if (access(var->command_m[0], X_OK | F_OK) == 0)
		return (ft_strdup(var->command_m[0]));
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
	return (NULL);
}
