/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:57:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/06 11:58:01 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	exe_export_var(t_ast_n *cmd, t_mini *mini);
static char	*is_var_in_env(t_ast_n *cmd,
				t_mini *mini, t_llst *llst, char *new_var);
static void	exe_export(t_mini *mini);
void	ft_put_export(t_ast_n *root);

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
		exe_export(mini);
	else
		exe_export_var(cmd, mini);
	g_status_child = 0;
	finished_builtin(cmd, mini, var);
}

static void	exe_export(t_mini *mini)
{
	t_builtin	v;

	v.line = mini->m_lst_env->head;
	v.index = 1;
	v.expor_sort = ft_init_ast();
	add_lexicographic_value(mini->m_lst_env, '=');
	while (v.index <= mini->m_lst_env->size)
	{
		ft_build_tree_lnode(v.expor_sort, v.line, v.line->lex_val);
		v.line = v.line->next;
		v.i_color++;
		v.index++;
	}
	ft_putstr_fd(mini->color[2], STDOUT_FILENO);
	ft_put_export(v.expor_sort->root);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_delete_tree(v.expor_sort);
}

static void	exe_export_var(t_ast_n *cmd, t_mini *mini)
{
	t_builtin	v;

	ft_remove_lst_front(cmd->m_lst->matrix);
	v.line = cmd->m_lst->matrix->head;
	while (cmd->m_lst->matrix->size)
	{
		v.new_var = get_prfx(find_type_rtrn_ptr(v.line->lst, EQUAL),
				v.line->lst);
		if (!v.new_var)
		{
			ft_remove_lst_front(cmd->m_lst->matrix);
			if (cmd->m_lst->matrix->size == 0)
				break ;
			v.line = cmd->m_lst->matrix->head;
		}
		v.new_var = is_var_in_env(cmd, mini, v.line, v.new_var);
		if (v.new_var && ft_strlen(v.new_var))
		{
			ft_add_mlstnode_back(mini->m_lst_env,
				mlst_rmv_return_lnode(cmd->m_lst->matrix, v.line));
			free(v.new_var);
		}
		v.line = cmd->m_lst->matrix->head;
	}
}

static char	*is_var_in_env(t_ast_n *cmd,
			t_mini *mini, t_llst *llst, char *new_var)
{
	t_builtin	v;

	v.env = mini->m_lst_env->head;
	v.index = 0;
	while (new_var && v.index < mini->m_lst_env->size)
	{
		v.prefix = NULL;
		v.prefix = get_prfx(find_type_rtrn_ptr(v.env->lst, EQUAL), v.env->lst);
		if (v.prefix && !ft_strncmp(new_var, v.prefix, ft_strlen(v.prefix) + 1))
		{
			ft_add_mlstnode_back(mini->m_lst_env,
				mlst_rmv_return_lnode(cmd->m_lst->matrix, llst));
			ft_rmv_spcfc_lst_mtrx(mini->m_lst_env, v.env);
			free(v.prefix);
			free(new_var);
			new_var = NULL;
			break ;
		}
		free(v.prefix);
		v.index++;
		v.env = v.env->next;
	}
	return (new_var);
}

void	ft_put_export(t_ast_n *root)
{
	if (root != NULL)
	{
		ft_put_export(root->left);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putlst_fd(root->line->lst, 1, STDOUT_FILENO);
		ft_put_export(root->right);
	}
}
