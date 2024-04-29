/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 18:49:37 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	ft_execute_tree(t_ast_node *root, t_mtrx_mtrx *mtrx_mtrx,
		t_mtrx_lst *env)
{
	if (root != NULL)
	{
		ft_execute_tree(root->left, mtrx_mtrx, env);
		ft_execute(root, env);
	}
}

static void ft_open_infile_02(t_mtrx_lst *mtrix);

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
		if (cmd->m_lst->next->type == PIPE)
		{
			dup2(tube[1], STDOUT_FILENO);
			close(tube[0]);
			close(tube[1]);
		}
		// TODO multiplos REDI_IN
		ft_open_infile_02(cmd->m_lst->matrix);
		/* if (cmd->m_lst->matrix->head->rdrct == REDI_IN)
		{
			var.infile = ft_cpy_lst_to_array(cmd->m_lst->matrix->head->lst);
			ft_open_infile(var.infile);
			ft_remove_lst_front(cmd->m_lst->matrix);
		} */
		// TODO multiplos REDI_OUT
		if (cmd->m_lst->matrix->last->rdrct == REDI_OUT)
		{
			var.outfile = ft_cpy_lst_to_array(cmd->m_lst->matrix->last->lst);
			ft_open_outfile(var.outfile);
			ft_remove_list_back(cmd->m_lst->matrix);
		}
		var.command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
		var.env = ft_path_env(env_list);
		var.path_exe = ft_get_executable(var.command_m[0], var.env);
		if (var.path_exe)
			execve(var.path_exe, &var.command_m[0], var.env);
		exit(1);
	}
	else
	{
		if (cmd->m_lst->next->type == PIPE)
		{
			dup2(tube[0], STDIN_FILENO);
			close(tube[0]);
			close(tube[1]);
		}
	}
}

static void ft_open_infile_02(t_mtrx_lst *mtrix)
{
	t_lst_line	*current;
	t_lst_line	*next;
	char		*infile;
	int			i;

	i = 1;
	current = mtrix->head;
	next = current->next;
	while (i <= mtrix->size)
	{
		if (current->rdrct == REDI_IN)
		{
			infile = ft_cpy_lst_to_array(current->lst);
			ft_open_infile(infile);
			ft_rmv_spcfc_lst_mtrx(mtrix, current);
			free(infile);
			i--;
		}
		i++;
		current = next;
		next = next->next;
	}
}