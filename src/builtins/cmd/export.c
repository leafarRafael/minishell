/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:57:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/05 12:17:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

/* static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_var_exe *var); */

int	ft_cmpvar(t_lst *lst, char *str, int size)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_cpy_lst_to_array(lst);
	printf("STR CPY [%s] PREFIX [%s] [len = %d]\n", new, str, size + 1);
	i = ft_memcmp(new, str, size + 1);
	free(new);
	// printf("RETURN [%d]\n", i);
	return (i);
}

t_node	*find_equal_return_ptr(t_lst *lst, char ch)
{
	int		i;
	t_node	*node;

	if (!lst)
		return (NULL);
	if (lst->size == 0)
		return (NULL);
	i = 1;
	node = lst->head;
	while (i <= lst->size)
	{
		if (node->c == ch)
		{
			// node = node->next;
			return (node);
		}
		i++;
		node = node->next;
	}
	return (NULL);
}

void export(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	t_llst	*line;
	int		i;
	int		i_color;

	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, var);
	ft_valid_command_builtin(cmd);
	g_status_child = 0;
	if (cmd->m_lst->matrix->size == 1)
	{
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
	else
	{
		t_llst	*llst;
		int		llst_size;

		llst = cmd->m_lst->matrix->head->next;
		llst_size = cmd->m_lst->matrix->size - 1;
		t_llst	*env;
		char	*prefix;
		char	*varrrr;
		int		index;
		while (llst_size)
		{
			env = mini->m_lst_env->head;
			index = 0;
			varrrr = get_prfx(find_equal_return_ptr(llst->lst, '='), llst->lst);
			while(ft_strlen(varrrr) && index < mini->m_lst_env->size)
			{
				prefix = NULL;
				prefix = get_prfx(find_type_rtrn_ptr(env->lst, EQUAL_SING), env->lst);
				if (prefix)
				{
					if (!ft_strncmp(varrrr, prefix, ft_strlen(prefix) + 1))
					{
						ft_add_mlstnode_back(mini->m_lst_env, mlst_rmv_return_lnode(cmd->m_lst->matrix, llst));
						ft_rmv_spcfc_lst_mtrx(mini->m_lst_env, env);
						free(prefix);
						free(varrrr);
						finished_builtin(cmd, mini, var);
						return ;
					}
				}
				free(prefix);
				index++;
				env = env->next;
			}
			if (ft_strlen(varrrr))
			{
				ft_add_mlstnode_back(mini->m_lst_env, mlst_rmv_return_lnode(cmd->m_lst->matrix, llst));
				free(varrrr);
			}

			llst = llst->next;
			llst_size--;
		}
	}
	finished_builtin(cmd, mini, var);
}

/* static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[1], STDOUT_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
	if (ft_redirect_manager(cmd->m_lst->matrix) < 0)
		free_memory(mini, var, 1);
}
 */