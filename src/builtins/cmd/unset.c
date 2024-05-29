/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:19:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/29 13:58:52 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_variable(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
char	*get_prefix(t_node *ptr, t_lst *lst);


void	unset(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	ft_manager_fd2(cmd, mini, ast, var);
	ft_valid_command2(cmd, mini, ast, var);
	remove_variable(cmd, mini, ast, var);
	finished_builtin2(cmd, mini, ast, var);
}

static void	remove_variable(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
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
		prefix = get_prefix(find_type_return_ptr(current->lst, EQUAL_SING), current->lst);
/* 		if (prefix)
			ft_putstr_fd(prefix, 2); */
		if (prefix)
		{
			if (!ft_strlstcmp(lst, prefix, ft_strlen(prefix)))
			{
				ft_putlst_fd(current->lst, 1, 2);
				ft_rmv_spcfc_lst_mtrx(mini->m_lst_env, current);
				ft_putstr_fd(prefix, 2);
				
				ft_putstr_fd("\n", 2);
				free(prefix);
				break ;
			}
		}
		free(prefix);
		i++;
		current = current->next;
	}
}

char	*get_prefix(t_node *ptr, t_lst *lst)
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