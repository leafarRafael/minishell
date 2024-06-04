/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:57:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 07:52:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prefix(t_node *ptr, t_lst *lst)
{
	t_node	*temp;
	t_lst	*lst_prefix;
	char	*prefix;

	if (!lst || !ptr)
		return (NULL);
	if (ptr == lst->head)
		return (NULL);
	temp = ptr->prev;
	lst_prefix = ft_init_lst();
	while (1)
	{
		ft_add_node_front(lst_prefix, ft_cpynode(temp));
		temp = temp->prev;
		if (temp == lst->last)
			break ;
		if (temp->type == WILDCARD)
			break ;
		if (temp->type != NO_OP_TYPE)
			break ;
	}
	prefix = ft_cpy_lst_to_array(lst_prefix);
	ft_delete_list(lst_prefix);
	return (prefix);
}

static char	*get_sufix(t_node *ptr, t_lst *lst)
{
	t_node	*temp;
	t_lst	*lst_prefix;
	char	*prefix;

	if (!lst || !ptr)
		return (NULL);
	if (ptr == lst->head)
		return (NULL);
	temp = ptr->next;
	lst_prefix = ft_init_lst();
	while (1)
	{
		ft_add_node_back(lst_prefix, ft_cpynode(temp));
		temp = temp->next;
		if (temp == lst->head)
			// return (NULL);
			break ;
		if (temp->type == WILDCARD)
			break ;
		if (temp->type != NO_OP_TYPE)
			break ;
	}
	prefix = ft_cpy_lst_to_array(lst_prefix);
	ft_delete_list(lst_prefix);
	return (prefix);
}

static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);

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

void export(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	t_llst	*line;
	int		i;
	int		i_color;

	if (cmd->m_lst->prev->type == AND_OP && status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && status_child == 0)
		return ;
	status_child = 0;
	ft_manager_fd(cmd, mini, ast, var);
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
			free_memory(mini, var, ast, 1);
		}
	}
	else
	{
		t_llst	*llst;
		t_node	*node;
		int		llst_size;
		int		node_size;

		llst = cmd->m_lst->matrix->head->next;
		llst_size = cmd->m_lst->matrix->size - 1;
		t_llst	*env;
		char	*prefix;
		char	*var;
		int		index;
		while (llst_size)
		{
			env = mini->m_lst_env->head;
			index = 0;
			prefix = NULL;
			var = NULL;
			// ft_print_array_lst(llst->lst, 0);
			var = get_prefix(find_equal_return_ptr(llst->lst, '='), llst->lst);
			// printf("===>>> VAR [ %s ]\n", var);
			while(ft_strlen(var) && index < mini->m_lst_env->size)
			{
				prefix = NULL;
				prefix = get_prefix(find_type_return_ptr(env->lst, EQUAL_SING), env->lst);
				if (prefix)
				{
					if (!ft_strncmp(var, prefix, ft_strlen(prefix) + 1))
					{
						// printf("===>>> PREFIX [ %s ]\n", prefix);
						ft_add_mlstnode_back(mini->m_lst_env, mlst_rmv_return_lnode(cmd->m_lst->matrix, llst));
						ft_rmv_spcfc_lst_mtrx(mini->m_lst_env, env);
						// ft_print_array_lst(llst->lst, 0);
						free(prefix);
						free(var);
						return ;
					}
				}
				free(prefix);
				index++;
				env = env->next;
			}
			if (ft_strlen(var))
			{
				// printf("ADD NEW VAR = \n");
				// ft_print_array_lst(llst->lst, 0);
				ft_add_mlstnode_back(mini->m_lst_env, mlst_rmv_return_lnode(cmd->m_lst->matrix, llst));
				free(var);
			}

			llst = llst->next;
			llst_size--;
		}
	}
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


static void	ft_valid_command(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->matrix->size == 1 && cmd->m_lst->matrix->head->lst->size == 0)
	{
		ft_msg_error("''", " command not found");
		free_memory(mini, var, ast, 126);
	}
	if (cmd->m_lst->matrix->size == 0)
		free_memory(mini, var, ast, 0);
}
