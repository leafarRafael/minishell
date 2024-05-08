/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/08 11:26:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void ft_execve(t_ast_n *cmd, t_mlst *env_list, t_mmlst *mmlst);

void	ft_execute(t_ast_n *cmd, t_mlst *env_list, t_mmlst *mmlst)
{
	t_lst		*new_lst;
	t_lst		*temp;
	int			i;

	i = 0;
	if (cmd == NULL)
		return ;
	ft_execute(cmd->left, env_list, mmlst);
	if (cmd->m_lst->matrix->head->lst->head->c == '(')
	{
		temp = cmd->m_lst->matrix->head->lst;
		new_lst = ft_duplst(temp, ft_cpynode, ft_add_node_back);
		ft_scanner_input(new_lst);
		ft_remove_specific_matrix(mmlst, cmd->m_lst);
		ft_remove_node_back(new_lst);
		ft_remove_node_front(new_lst);
		ft_parse_exe(new_lst, env_list, mmlst);
	}
	else
	{
/* 		if (cmd->m_lst->next->type == PIPE)
		{
			ft_print_matrix_line(cmd->m_lst->next->matrix);
			ft_remove_specific_matrix(mmlst, cmd->m_lst->next);

		}
		ft_print_matrix_line(cmd->m_lst->matrix);
		ft_remove_specific_matrix(mmlst, cmd->m_lst); */
		ft_execve(cmd, env_list, mmlst);
	}
		
		
}

static void ft_execve(t_ast_n *cmd, t_mlst *env_list, t_mmlst *mmlst)
{
	t_var_exe	var;
	int			tube[2];
	
	if (cmd->m_lst->next->type == PIPE)
		pipe(tube);
	ft_redirect(cmd->m_lst->matrix);
	var.pid = fork();
	if (var.pid == 0)
	{
		ft_remove_quote_m_lst(cmd->m_lst->matrix);
		ft_expand_m_lst(cmd->m_lst->matrix);
		if (cmd->m_lst->next->type == PIPE)
		{
			dup2(tube[1], STDOUT_FILENO);
			close(tube[0]);
			close(tube[1]);
		}
		var.env = ft_path_env(env_list);
		var.command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
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
		if (cmd->m_lst->next->type == PIPE)
			ft_remove_specific_matrix(mmlst, cmd->m_lst->next);
		ft_remove_specific_matrix(mmlst, cmd->m_lst);
	}
}