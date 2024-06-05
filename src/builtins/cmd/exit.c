/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:37 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/05 12:17:53 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	exe_exit(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
static int	valid_number(t_lst *lst);

void	my_exit(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (!cmd)
		return ;
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, var);
	ft_valid_command_builtin(cmd);
	if (cmd->m_lst->matrix->size == 1)
	{
		ft_putlst_fd(cmd->m_lst->matrix->head->lst, 1, 2);
		free_memory(mini, var, g_status_child);
	}
	exe_exit(cmd, mini, var);
}

static void	exe_exit(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	char	*nbr_exit;
	int		nbr;

	if (cmd->m_lst->matrix->size > 2)
	{
		ft_msg_error("exit", "too many arguments");
		g_status_child = 1;
		return ;
	}
	ft_remove_lst_front(cmd->m_lst->matrix);
	nbr_exit = ft_cpy_lst_to_array(cmd->m_lst->matrix->head->lst);
	if (valid_number(cmd->m_lst->matrix->head->lst)
		|| cmd->m_lst->matrix->head->lst->size > 19)
	{
		ft_msg_error(nbr_exit, "numeric argument required");
		g_status_child = 2;
		free(nbr_exit);
		return ;
	}
	nbr = ft_atoi(nbr_exit);
	free(nbr_exit);
	free_memory(mini, var, nbr);
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
