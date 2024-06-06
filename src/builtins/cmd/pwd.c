/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:21:05 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/06 10:21:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	getpwd(void);

void	pwd(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, var);
	ft_valid_command_builtin(cmd);
	getpwd();
	finished_builtin(cmd, mini, var);
}

static void	getpwd(void)
{
	char	*current_dir;
	char	buf[256];

	current_dir = getcwd(buf, 256);
	if (current_dir)
	{
		ft_putstr_fd(current_dir, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
