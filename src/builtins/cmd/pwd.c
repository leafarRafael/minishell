/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:21:05 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/28 14:43:52 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);

static int	ft_find_str_inlist2(t_lst *lst, char *str, int size);

void	pwd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	t_llst	*node;

	ft_manager_fd(cmd, mini, ast, var);
	node = mini->m_lst_env->head;
	while(node->next != mini->m_lst_env->head)
	{
		if (!ft_find_str_inlist2(node->lst, "PWD=", 4))
		{
			ft_putstr_fd(mini->color[0], STDOUT_FILENO);
			ft_putlst_fd(node->lst, 1, STDOUT_FILENO);
			ft_putstr_fd(RESET, STDOUT_FILENO);
			break ;
		}
		node = node->next;
	}
	if (cmd->m_lst->next->type == PIPE || cmd->m_lst->prev->type == PIPE)
	{
		close (mini->fd_std[0]);
		close (mini->fd_std[1]);
		status_child = 0;
		free_memory(mini, var, ast, status_child);
	}
}

static int	ft_find_str_inlist2(t_lst *lst, char *str, int size)
{
	t_var	v;
	char	*new;
	int		i;

	i = 0;
	new = ft_cpy_lst_to_array(lst);
	i = memcmp(str, new, size);
	free(new);
	return (i);
}

static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[1], STDOUT_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
	if (ft_redirect_manager(cmd->m_lst->matrix) < 0)
		free_memory(mini, var, ast, 1);
}