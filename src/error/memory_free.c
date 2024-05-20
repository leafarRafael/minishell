/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:08:21 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/20 09:26:45 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_close();

void free_memory(t_mini *mini, t_var_exe *var, t_ast *ast, int status_exit)
{
	if (mini)
	{
		if (mini->mmlst)
			ft_delete_mmlst(mini->mmlst);
		if (mini->m_lst_env)
			ft_delete_matrix(mini->m_lst_env);
		if (mini->env)
			ft_delete_cmatrix(mini->env);
	}
	if (ast)
		ft_delete_tree(ast);
	if (var)
	{
		if (var->path_exe)
			free(var->path_exe);
		if (var->env)
			ft_delete_cmatrix(var->env);
		if (var->command_m)
			ft_delete_cmatrix(var->command_m);
	}
	ft_close();
	exit(status_exit);
}

static void ft_close(void)
{
	close(0);
	close(1);
	close(2);
}

