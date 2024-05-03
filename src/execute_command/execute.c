/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/03 10:23:54 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	ft_execute(t_ast_node *cmd, t_mtrx_lst *env_list)
{
	t_var_exe	var;
	int			tube[2];

	if (cmd == NULL)
		return ;
	if (cmd->m_lst->next->type == PIPE)
		pipe(tube);
	var.pid = fork();
	if (var.pid == 0)
	{
		ft_execute(cmd->left, env_list);
		if (cmd->m_lst->matrix->head->lst->head->c == '(')
		{
			ft_parse_and_execute(cmd->m_lst->matrix->head->lst, env_list);
			exit(1);
		}
		here_doc(cmd->m_lst->matrix);

		ft_remove_quote_m_lst(cmd->m_lst->matrix);
		ft_expand_m_lst(cmd->m_lst->matrix);
		if (cmd->m_lst->next->type == PIPE)
		{
			dup2(tube[1], STDOUT_FILENO);
			close(tube[0]);
			close(tube[1]);
		}
		ft_opens_all_input_files(cmd->m_lst->matrix);
		ft_opens_all_output_files_truncate(cmd->m_lst->matrix);
		ft_opens_all_output_files_append(cmd->m_lst->matrix);
		var.command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
		var.env = ft_path_env(env_list);
		var.path_exe = ft_get_executable(var.command_m[0], var.env);
		if (var.path_exe)
			execve(var.path_exe, &var.command_m[0], var.env);
		exit(1);
	}
	else
	{
		wait(&var.pid);
		if (cmd->m_lst->next->type == PIPE)
		{
			dup2(tube[0], STDIN_FILENO);
			close(tube[0]);
			close(tube[1]);
		}
	}
}
