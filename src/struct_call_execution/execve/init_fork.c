/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:39:49 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/23 15:41:38 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fork(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	var->pid = fork();
	if (var->pid == 0)
		children(cmd, mini, ast, var);
	else
	{
		parent(cmd, mini, var);
		free_cmd_operator_executed(cmd, mini);
	}
}