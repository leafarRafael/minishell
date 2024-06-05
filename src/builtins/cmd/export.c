/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:57:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/05 19:13:13 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	exe_export(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	t_llst	*line;
	int		i;
	int		i_color;

	line = mini->m_lst_env->head;
	i = 1;
	i_color = 0;
	while (i <= mini->m_lst_env->size)
	{
		if (i_color > 3)
			i_color = 0;
		ft_putstr_fd(mini->color[i_color], STDOUT_FILENO);
		ft_putlst_fd(line->lst, 1, STDOUT_FILENO);
		ft_putstr_fd(RESET, STDOUT_FILENO);
		i_color++;
		line = line->next;
		i++;
	}
	if (cmd->m_lst->next->type == PIPE)
	{
		close (mini->fd_std[0]);
		close (mini->fd_std[1]);
		free_memory(mini, var, 1);
	}
}

char	*is_var_in_env(t_ast_n *cmd, t_mini *mini, t_llst *llst, char *new_var)
{
	t_llst	*env;
	char	*prefix;
	int		index;

	env = mini->m_lst_env->head;
	index = 0;
	while (new_var && index < mini->m_lst_env->size)
	{
		prefix = NULL;
		prefix = get_prfx(find_type_rtrn_ptr(env->lst, EQUAL_SING), env->lst);
		if (prefix && !ft_strncmp(new_var, prefix, ft_strlen(prefix) + 1))
		{
			ft_add_mlstnode_back(mini->m_lst_env,
				mlst_rmv_return_lnode(cmd->m_lst->matrix, llst));
			ft_rmv_spcfc_lst_mtrx(mini->m_lst_env, env);
			free(prefix);
			free(new_var);
			new_var = NULL;
			break ;
		}
		free(prefix);
		index++;
		env = env->next;
	}
	return (new_var);
}

void	exe_export_var(t_ast_n *cmd, t_mini *mini)
{
	t_llst	*llst;
	char	*new_var;

	ft_remove_lst_front(cmd->m_lst->matrix);
	llst = cmd->m_lst->matrix->head;
	while (cmd->m_lst->matrix->size)
	{
		new_var = get_prfx(find_type_rtrn_ptr(llst->lst, EQUAL_SING),
				llst->lst);
		if (!new_var)
		{
			ft_remove_lst_front(cmd->m_lst->matrix);
			if (cmd->m_lst->matrix->size == 0)
				break ;
			llst = cmd->m_lst->matrix->head;
		}
		new_var = is_var_in_env(cmd, mini, llst, new_var);
		if (new_var && ft_strlen(new_var))
		{
			ft_add_mlstnode_back(mini->m_lst_env,
				mlst_rmv_return_lnode(cmd->m_lst->matrix, llst));
			free(new_var);
		}
		llst = cmd->m_lst->matrix->head;
	}
}

void	export(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, var);
	ft_valid_command_builtin(cmd);
	g_status_child = 0;
	if (cmd->m_lst->matrix->size == 1)
		exe_export(cmd, mini, var);
	else
		exe_export_var(cmd, mini);
	finished_builtin(cmd, mini, var);
}
