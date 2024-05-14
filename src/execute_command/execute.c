/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/14 18:59:34 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void ft_execve(t_ast_n *cmd, t_mini *mini, t_ast *ast);
static void ft_expand_subshell(t_ast_n *cmd, t_mini *mini, t_ast *ast);
static int	ft_valid_next(t_mlst *mlst);

void	ft_execute(t_ast_n *cmd, t_mini *mini, t_ast *ast)
{
	if (cmd == NULL)
		return ;
	if (ft_valid_next(cmd->m_lst->matrix))
	{
		ft_print_matrix_line(cmd->m_lst->matrix);
		if (ft_redirect(cmd->m_lst->matrix) < 0)
			return ;
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
		ft_execute(cmd->left, mini, ast);
		return ;
	}
	else
		ft_execute(cmd->left, mini, ast);
	if (cmd->m_lst->matrix->head->lst->head->c == '(')
		ft_expand_subshell(cmd, mini, ast);
	else
		ft_execve(cmd, mini, ast);
}

static void ft_expand_subshell(t_ast_n *cmd, t_mini *mini, t_ast *ast)
{
	t_lst		*new_lst;
	t_lst		*temp;

	temp = cmd->m_lst->matrix->head->lst;
	new_lst = ft_duplst(temp, ft_cpynode, ft_add_node_back);
	ft_scanner_input(new_lst);
	ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
	ft_remove_node_back(new_lst);
	ft_remove_node_front(new_lst);
	ft_parse_exe(new_lst, mini);
}

static void ft_execve(t_ast_n *cmd, t_mini *mini, t_ast *ast)
{
	t_var_exe	var;
	int			tube[2];
	
	if (cmd == NULL)
		return ;
	if (ft_redirect(cmd->m_lst->matrix) < 0)
		return ;
	if (cmd->m_lst->matrix->size == 0)
	{
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
		return  ;
	}
	if (cmd->m_lst->next->type == PIPE)
		pipe(tube);
	var.pid = fork();
	if (var.pid == 0)
	{
		ft_expand_m_lst(cmd->m_lst->matrix);
		ft_remove_quote_m_lst(cmd->m_lst->matrix);
		if (cmd->m_lst->next->type == PIPE)
		{
			dup2(tube[1], STDOUT_FILENO);
			close(tube[0]);
			close(tube[1]);
		}
		var.env = ft_path_env(mini->m_lst_env);
		var.command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
		var.path_exe = ft_get_executable(var.command_m[0], var.env);
		if (var.path_exe)
			execve(var.path_exe, &var.command_m[0], var.env);
		free_memory(mini, &var,ast);
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
			ft_remove_specific_matrix(mini->mmlst, cmd->m_lst->next);
		ft_remove_specific_matrix(mini->mmlst, cmd->m_lst);
	}
}

static int	ft_valid_next(t_mlst *mlst)
{
	t_lst_line	*line;
	int			op_redir;
	int			i;

	i = 0;
	op_redir = 0;
	line = mlst->head;
	while (i <= mlst->size)
	{
		if (line->rdrct != -42)
			op_redir++;
		i++;
		line = line->next;
	}
	if (i == op_redir)
		return (-1);
	return (0);
}