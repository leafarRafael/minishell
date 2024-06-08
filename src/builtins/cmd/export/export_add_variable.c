/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:35:32 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/08 19:56:57 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static char	*var_in_env(t_ast_n *cmd, t_mini *mini, t_llst *llst, char *new_var);
static int	valid_var_declar(t_lst *lst);
static int	valid_prefix(char c);
static int	valid_infix(char c);

void	export_addvar(t_ast_n *cmd, t_mini *mini)
{
	t_builtin	v;

	ft_remove_lst_front(cmd->m_lst->matrix);
	v.line = cmd->m_lst->matrix->head;
	mini->status = 0;
	while (cmd->m_lst->matrix->size)
	{
		if (valid_var_declar(v.line->lst))
		{
			ft_putstr_fd("export: ", 2);
			ft_putlst_fd(v.line->lst, 0, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			ft_remove_lst_front(cmd->m_lst->matrix);
			mini->status = 1;
			if (cmd->m_lst->matrix->size == 0)
				break ;
			v.line = cmd->m_lst->matrix->head;
		}
		else
		{
			v.new_var = get_prfx(find_type_rtrn_ptr(v.line->lst, EQUAL), v.line->lst);
			if (!v.new_var)
			{
				ft_remove_lst_front(cmd->m_lst->matrix);
				if (cmd->m_lst->matrix->size == 0)
					break ;
				v.line = cmd->m_lst->matrix->head;
			}
			v.new_var = var_in_env(cmd, mini, v.line, v.new_var);
			if (v.new_var && ft_strlen(v.new_var))
			{
				ft_add_mlstnode_back(mini->m_lst_env,
					mlst_rmv_return_lnode(cmd->m_lst->matrix, v.line));
				free(v.new_var);
			}
			v.line = cmd->m_lst->matrix->head;
		}
	}
	mini->ctrl_pid++;
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

static int	valid_var_declar(t_lst *lst)
{
	t_node	*node;
	int		i;

	if (!lst)
		return (1);
	if (lst->size == 0)
		return (1);
	if (!valid_prefix(lst->head->c))
		return (1);
	if (lst->size == 2 && lst->head->next->c == '=')
		return (0);
	i = 1;
	node = lst->head->next;
	while (i < lst->size && node->c != '=')
	{
		if (!valid_infix(node->c))
			return (1);
		node = node->next;
		i++;
	}
	return (0);
}

static int	valid_prefix(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c == '_'));
}

static int	valid_infix(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| (c == '_'));
}
