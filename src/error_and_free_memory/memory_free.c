/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:08:21 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/30 14:07:59 by rbutzke          ###   ########.fr       */
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
			ft_delcmtrx(mini->env);
		if (mini->color)
			ft_delcmtrx(mini->color);
	}
	if (ast)
		ft_delete_tree(ast);
	if (var)
	{
		if (var->path_exe)
			free(var->path_exe);
		if (var->env)
			ft_delcmtrx(var->env);
		if (var->command_m)
			ft_delcmtrx(var->command_m);
	}
	ft_close(mini->fd_std);
	exit(status_exit);
}

static void ft_close(int fd_std[2])
{
	close(fd_std[0]);
	close(fd_std[1]);
	close(0);
	close(1);
	close(2);
}

