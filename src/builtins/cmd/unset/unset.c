/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:19:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/09 11:36:07 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static void	remove_variable(t_ast_n *cmd, t_mini *mini);
static int	find_var_and_remove(t_lst *lst, t_llst *line, t_mlst *env);

void	unset(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, var);
	ft_valid_command_builtin(cmd);
	ft_status_builtin(mini, 0, INIT_SUCCESS);
	if (cmd->m_lst->matrix->size > 1)
		remove_variable(cmd, mini);
	finished_builtin(cmd, mini, var);
}

static void	remove_variable(t_ast_n *cmd, t_mini *mini)
{
	t_builtin	v;

	ft_remove_lst_front(cmd->m_lst->matrix);
	if (cmd->m_lst->matrix->size == 0)
		return ;
	v.line = mini->m_lst_env->head;
	v.list = cmd->m_lst->matrix->head->lst;
	v.index = 0;
	if (valid_var_declar(v.list))
	{
		ft_putstr_fd("unset: ", 2);
		ft_putlst_fd(v.list, 0, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		ft_status_builtin(mini, 1, __ERROR);
		remove_variable(cmd, mini);
		return ;
	}
	while (v.index < mini->m_lst_env->size)
	{
		if (find_var_and_remove(v.list, v.line, mini->m_lst_env))
			break ;
		v.index++;
		v.line = v.line->next;
	}
	remove_variable(cmd, mini);
}

static int	find_var_and_remove(t_lst *lst, t_llst *line, t_mlst *env)
{
	char	*prefix;

	prefix = NULL;
	prefix = get_prfx(find_type_rtrn_ptr(line->lst, EQUAL), line->lst);
	if (prefix)
	{
		if (!ft_strlstcmp(lst, prefix))
		{
			ft_rmv_spcfc_lst_mtrx(env, line);
			free(prefix);
			return (1);
		}
	}
	free(prefix);
	return (0);
}
