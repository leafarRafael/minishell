/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:37 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/03 12:08:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exit(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	ft_manager_fd_builtin(cmd, mini, ast, var);
	ft_valid_command_builtin(cmd, mini, ast, var);
	free_memory(mini, var, ast, 0);
}

int	ft_exit(char *input)
{
	int	i;

	if (!input)
		return (-1);
	i = 0;
	while (ft_words_delemiter(input[i]))
		i++;
	if (ft_strncmp("exit2", &input[i], 5) == 0)
	{
		free(input);
		input = NULL;
		return (0);
	}
	return (-1);
}
