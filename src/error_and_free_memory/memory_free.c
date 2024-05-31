/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:08:21 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/31 19:08:04 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_close();

// void free_BUILTIN_memory(t_mini *mini, t_var_exe *var, t_ast *ast, int status_exit)

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

	int	index = 0;
	while (mini->ast[index]  && index < 40)
	{
		ft_printf("INDEX = [%d]\n", index);
		ft_delete_tree(mini->ast[index]);
		mini->ast[index] = NULL;
		index++;
	}

	// if (ast)1
	// 	ft_delete_tree(ast);

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
