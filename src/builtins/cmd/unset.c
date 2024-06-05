/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:19:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/05 12:18:07 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	remove_variable(t_ast_n *cmd, t_mini *mini);

void	unset(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, var);
	ft_valid_command_builtin(cmd);
	remove_variable(cmd, mini);
	g_status_child = 0;
	finished_builtin(cmd, mini, var);
}

static void	remove_variable(t_ast_n *cmd, t_mini *mini)
{
	t_llst	*current;
	t_lst	*lst;
	char	*prefix;
	int		i;

	lst = cmd->m_lst->matrix->head->next->lst;
	current = mini->m_lst_env->head;
	i = 0;
	prefix = NULL;
	while (i < mini->m_lst_env->size)
	{
		prefix = NULL;
		prefix = get_prfx(find_type_rtrn_ptr(current->lst, EQUAL_SING), current->lst);
		if (prefix)
		{
			if (!ft_strlstcmp(lst, prefix))
			{
				ft_rmv_spcfc_lst_mtrx(mini->m_lst_env, current);
				free(prefix);
				break ;
			}
		}
		free(prefix);
		i++;
		current = current->next;
	}
}
