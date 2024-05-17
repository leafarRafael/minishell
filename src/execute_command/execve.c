/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:52:21 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/17 10:45:49 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_parent(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe	*var);
static void children(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
static void count_redir(t_mlst *mtrix, t_lst_line *line, int *redir);
static int valid_redirect(t_mlst *mtrix);

void ft_execve(t_ast_n *cmd, t_mini *mini, t_ast *ast)
{
	t_var_exe	var;

	if (cmd == NULL)
		return ;
	if (cmd->m_lst->prev->type == AND_OP && status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && status_child == 0)
		return ;
	if (cmd->m_lst->next->type == PIPE)
		pipe(var.tube);
	var.pid = fork();
	if (var.pid == 0)
		children(cmd, mini, ast, &var);
	else
		ft_parent(cmd, mini, ast, &var);
}

static void ft_parent(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe	*var)
{
	waitpid(-1, &status_child, 2);
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[0], STDIN_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
	if (cmd->m_lst->next->type == PIPE)
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst->next);
	ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
}

static void children(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe	*var)
{
	ft_expand_m_lst(cmd->m_lst->matrix);
	ft_remove_quote_m_lst(cmd->m_lst->matrix);
	if (valid_redirect(cmd->m_lst->matrix) == 0)
		dup2(mini->fd_std[1], STDOUT_FILENO);
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[1], STDOUT_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
	if (ft_redirect(cmd->m_lst->matrix) < 0)
		return ;
	var->env = ft_path_env(mini->m_lst_env);
	var->command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
	var->path_exe = ft_get_executable(var->command_m[0], var->env);
	close (mini->fd_std[0]);
	close (mini->fd_std[1]);
	if (var->path_exe)
		execve(var->path_exe, &var->command_m[0], var->env);
	free_memory(mini, var, ast);
	status_child = 10;
	exit(status_child);
}

static int valid_redirect(t_mlst *mtrix)
{
	t_redirect	v;
	int			redir;

	redir = 0;
	v.index = 1;
	v.c = mtrix->head;
	v.next = v.c->next;
	v.size = mtrix->size;
	if (mtrix->size == 1)
	{
		count_redir(mtrix, v.c, &redir);
		return (redir);
	}
	while (v.index <= v.size)
	{
		count_redir(mtrix, v.c, &redir);
		v.index++;
		v.c = v.next;
		v.next = v.next->next;
	}
	return (redir);
}

static void count_redir(t_mlst *mtrix, t_lst_line *line, int *redir)
{
	if (line->rdrct == APPEND)
		(*redir)++;
	if (line->rdrct == HERE_DOC)
		(*redir)++;
	if (line->rdrct == REDI_IN)
		(*redir)++;
	if (line->rdrct == REDI_OUT)
		(*redir)++;
}
