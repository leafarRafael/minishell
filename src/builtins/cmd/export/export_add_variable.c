/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:35:32 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/13 08:54:12 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static char	*var_in_env(t_ast_n *cmd,
				t_mini *mini, t_llst *llst, char *new_var);
static int	ft_invalid_var(t_mlst *mlst, t_mini *mini, t_lst *lst);
static int	add(t_ast_n *cmd, t_mini *mini, t_llst *llst);

void	export_addvar(t_ast_n *cmd, t_mini *mini)
{
	t_builtin	v;

	ft_remove_lst_front(cmd->m_lst->matrix);
	v.line = cmd->m_lst->matrix->head;
	while (cmd->m_lst->matrix->size)
	{
		if (valid_var_declar(v.line->lst))
		{
			if (ft_invalid_var(cmd->m_lst->matrix, mini, v.line->lst))
				break ;
		}
		else
		{
			if (add(cmd, mini, v.line))
				break ;
		}
		v.line = cmd->m_lst->matrix->head;
	}
}

static char	*var_in_env(t_ast_n *cmd, t_mini *mini, t_llst *llst, char *new_var)
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

static int	ft_invalid_var(t_mlst *mlst, t_mini *mini, t_lst *lst)
{
	ft_status_builtin(mini, 1, __ERROR);
	ft_msg_error_lst(EXPORT, lst, NV_INDT);
	ft_remove_lst_front(mlst);
	if (mlst->size == 0)
		return (1);
	return (0);
}

static int	add(t_ast_n *cmd, t_mini *mini, t_llst *llst)
{
	char	*str;

	//str = get_prfx(find_type_rtrn_ptr(llst->lst, EQUAL), llst->lst);
	str = ft_cpy_lst_to_array(llst->lst);
	if (!str)
	{
		ft_remove_lst_front(cmd->m_lst->matrix);
		if (cmd->m_lst->matrix->size == 0)
			return (1);
		llst = cmd->m_lst->matrix->head;
	}
	str = var_in_env(cmd, mini, llst, str);
	if (str && ft_strlen(str))
	{
		ft_add_mlstnode_back(mini->m_lst_env,
			mlst_rmv_return_lnode(cmd->m_lst->matrix, llst));
		free(str);
	}
	return (0);
}
