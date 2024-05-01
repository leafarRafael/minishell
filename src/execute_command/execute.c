/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/01 14:46:58 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void ft_open_infile_02(t_mtrx_lst *mtrix);
static void ft_open_outfile_02(t_mtrx_lst *mtrix);

void	ft_execute(t_var_minishell *v, t_ast_node *cmd, t_mtrx_lst *env_list)
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
		ft_execute(v, cmd->left, env_list);
		ft_remove_quote_m_lst(cmd->m_lst->matrix);
		ft_expand_m_lst(cmd->m_lst->matrix);
		if (cmd->m_lst->next->type == PIPE)
		{
			dup2(tube[1], STDOUT_FILENO);
			close(tube[0]);
			close(tube[1]);
		}
		ft_open_infile_02(cmd->m_lst->matrix);
		ft_open_outfile_02(cmd->m_lst->matrix);
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
	int			size;

	i = 1;
	current = mtrix->head;
	next = current->next;
	size = mtrix->size;
	while (i <= size)
	{
		if (current->rdrct == REDI_IN)
		{
			infile = ft_cpy_lst_to_array(current->lst);
			ft_open_infile(infile);
			ft_rmv_spcfc_lst_mtrx(mtrix, current);
			free(infile);
		}
		i++;
		current = next;
		next = next->next;
	}
}

static void ft_open_outfile_02(t_mtrx_lst *mtrix)
{
	t_lst_line	*current;
	t_lst_line	*next;
	char		*outfile;
	int			i;
	int			size;

	i = 1;
	current = mtrix->head;
	next = current->next;
	size = mtrix->size;
	while (i <= size)
	{
		if (current->rdrct == REDI_OUT)
		{
			outfile = ft_cpy_lst_to_array(current->lst);
			ft_open_outfile(outfile);
			ft_rmv_spcfc_lst_mtrx(mtrix, current);
			free(outfile);
		}
		i++;
		current = next;
		next = next->next;
	}
}

/* static void ft_open_outfile_02(t_mtrx_lst *mtrix)
{
	t_lst_line	*current;
	t_lst_line	*next;
	char		*outfile;
	int			i;
	int			size;

	i = 1;
	current = mtrix->head;
	next = current->next;
	size = mtrix->size;
	while (i <= size)
	{
		if (current->rdrct == REDI_OUT)
		{
			outfile = ft_cpy_lst_to_array(current->lst);
			ft_open_outfile(outfile);
			ft_rmv_spcfc_lst_mtrx(mtrix, current);
			free(outfile);
		}
		i++;
		current = next;
		next = next->next;
	}
} */