/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:37 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 10:48:53 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exe_exit(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
static int	valid_number(t_lst *lst);

void	my_exit(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (!cmd)
		return ;
	if (cmd->m_lst->prev->type == AND_OP && status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, ast, var);
	ft_valid_command_builtin(cmd, mini, ast, var);
	if (cmd->m_lst->matrix->size == 1)
	{
		ft_putlst_fd(cmd->m_lst->matrix->head->lst, 1, 2);
		free_memory(mini, var, ast, status_child);
	}
	exe_exit(cmd, mini, ast, var);
}

static void	exe_exit(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	char	*nbr_exit;
	int		nbr;

	if (cmd->m_lst->matrix->size > 2)
	{
		ft_msg_error("exit", "too many arguments");
		status_child = 1;
		return ;
	}
	ft_remove_lst_front(cmd->m_lst->matrix);
	if (valid_number(cmd->m_lst->matrix->head->lst))
	{
		ft_msg_error(nbr_exit, "numeric argument required");
		status_child = 2;
		return ;
	}
	nbr_exit = ft_cpy_lst_to_array(cmd->m_lst->matrix->head->lst);
	nbr = ft_atoi(nbr_exit);
	free(nbr_exit);
	free_memory(mini, var, ast, nbr);
}

static int	valid_number(t_lst *lst)
{
	t_node	*node;
	int		i;

	node = lst->head;
	i = 0;
	while (i < lst->size)
	{
		if (!ft_isdigit(node->c))
			return (1);
		i++;
		node = node->next;
	}
	return (0);
}
