/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:08:21 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/13 15:36:43 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close(int fd_std[2]);
static void	free_mini(t_mini *mini);
static void	free_var(t_var_exe *var);

void	free_memory(t_mini *mini, t_var_exe *var, int status_exit)
{
	rl_clear_history();
	free_mini(mini);
	free_var(var);
	ft_close(mini->fd_std);
	ft_putstr_fd(RESET, 2);
	exit(status_exit);
}

static void	ft_close(int fd_std[2])
{
	close(fd_std[0]);
	close(fd_std[1]);
	close(0);
	close(1);
	close(2);
}

static void	free_mini(t_mini *mini)
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
		if (mini->collect)
			del_cllctr(mini->collect, NULL);
		if (mini->collect_ast)
			del_cllctr(mini->collect_ast, ft_delete_tree);
	}
}

static void	free_var(t_var_exe *var)
{
	if (var)
	{
		if (var->path_exe)
			free(var->path_exe);
		if (var->env)
			ft_delcmtrx(var->env);
		if (var->command_m)
			ft_delcmtrx(var->command_m);
	}
}
