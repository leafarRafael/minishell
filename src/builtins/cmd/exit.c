/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:37 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/10 20:48:15 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	exe_exit(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
static int	valid_number(char *nbr);

void	my_exit(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	if (ft_manager_fd_builtin(cmd, mini, var))
	{
		ft_status_builtin(mini, 1, __ERROR);
		return ;
	}
	ft_valid_command_builtin(cmd);
	ft_status_builtin(mini, 0, INIT_SUCCESS);
	ft_putstr_fd(RESET, 2);
	if (cmd->m_lst->matrix->size == 1)
	{
		ft_putlst_fd(cmd->m_lst->matrix->head->lst, 1, STDOUT_FILENO);
		free_memory(mini, var, g_status_child);
	}
	exe_exit(cmd, mini, var);
}

static void	exe_exit(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	t_builtin	v;

	if (cmd->m_lst->matrix->size > 2)
	{
		ft_msg_error("exit", "too many arguments");
		ft_status_builtin(mini, 1, __ERROR);
		free_memory(mini, var, g_status_child);
		return ;
	}
	ft_remove_lst_front(cmd->m_lst->matrix);
	v.nbr_exit = ft_cpy_lst_to_array(cmd->m_lst->matrix->head->lst);
	if (valid_number(v.nbr_exit)
		|| cmd->m_lst->matrix->head->lst->size > 19)
	{
		ft_msg_error(v.nbr_exit, "numeric argument required");
		ft_status_builtin(mini, 2, __ERROR);
		free(v.nbr_exit);
		free_memory(mini, var, g_status_child);
		return ;
	}
	v.nbr = ft_atoi(v.nbr_exit);
	free(v.nbr_exit);
	free_memory(mini, var, v.nbr);
}

static int	valid_number(char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i] == '-' || nbr[i] == '+')
		i++;
	if (nbr[i] == '\0')
		return (1);
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (1);
		i++;
	}
	return (0);
}
