/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:17:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/28 18:34:33 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

void	ft_execute_simple_cmd4(int tty[2], t_ast_node *cmd, t_mtrx_lst *env_list);
void	ft_execute_simple_cmd3(t_ast_node *cmd, t_mtrx_lst *env_list);
void	ft_execute_simple_cmd2(t_ast_node *cmd, t_mtrx_lst *env_list);
void	ft_execute_simple_cmd5(t_ast_node *cmd, t_mtrx_lst *env_list);

void ft_execute_tree(int tty[2], t_ast_node *root, t_mtrx_mtrx *mtrx_mtrx, t_mtrx_lst *env)
{
	if (root != NULL)
	{
		ft_execute_tree(tty, root->left, mtrx_mtrx, env);
		ft_execute_simple_cmd4(tty, root, env);
	}
}

void	ft_execute_simple_cmd(t_var_minishell *mini)
{
	t_var_exe	var;

	var.pid = fork();
	if (var.pid == 0)
	{
		var.command_m = ft_cpy_mtrllst_to_cmtrx(mini->list_matrix->head->matrix);
		var.env = ft_path_env(mini->mrtx_lst_env);
		var.path_exe = ft_get_executable(var.command_m[0], var.env);
		if (var.path_exe)
			execve(var.path_exe, var.command_m, var.env);
	}
}

void	ft_execute_simple_cmd3(t_ast_node *cmd, t_mtrx_lst *env_list)
{
	t_var_exe	var;

	var.pid = fork();
	if (var.pid == 0)
	{
		if (cmd->m_lst->matrix->head->lst->head->type == REDI_IN)
		{
			ft_remove_lst_front(cmd->m_lst->matrix);
			var.infile = ft_cpy_lst_to_array(cmd->m_lst->matrix->head->lst);
			ft_open_infile(var.infile);
			ft_remove_lst_front(cmd->m_lst->matrix);
		}
		var.command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
		var.env = ft_path_env(env_list);
		var.path_exe = ft_get_executable(var.command_m[0], var.env);
		if (var.path_exe)
			execve(var.path_exe, &var.command_m[0], var.env);
		exit(1);
	}
}

void	ft_execute_simple_cmd2(t_ast_node *cmd, t_mtrx_lst *env_list)
{
	t_var_exe	var;
	int			i;

	i = 0;
	var.pid = fork();
	if (var.pid == 0)
	{
		var.command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
		if (cmd->m_lst->prev->type == REDI_IN)
		{
			ft_open_infile(var.command_m[i]);
			i++;
		}
		if (i > 0 )
			ft_remove_lst_front(cmd->m_lst->matrix);
		var.env = ft_path_env(env_list);
		var.path_exe = ft_get_executable(var.command_m[i], var.env);
		if (var.path_exe)
			execve(var.path_exe, &var.command_m[i], var.env);
		exit(1);
	}
}


char	*ft_get_executable(char *command, char **path)
{
	int		i;
	char	*temp;

	i = 0;
	if (access(command, X_OK | F_OK) == 0)
		return (ft_strdup(command));
	temp = NULL;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		temp = ft_strjoin(temp, command);
		if (access(temp, X_OK | F_OK) == 0)
			return (temp);
		free(temp);
		temp = NULL;
		i++;
	}
	return (NULL);
}


void	ft_execute_simple_cmd4(int tty[2], t_ast_node *cmd, t_mtrx_lst *env_list)
{
	t_var_exe	var;
	int			tube[2];

	// TODO
	// if (cmd->m_lst->prev->status != 0 && cmd->op == AND)
	// 	return ;
	if (cmd->m_lst->next->type == PIPE)
		pipe(tube);
	var.pid = fork();
	if (var.pid == 0)
	{
		if (cmd->m_lst->next->type == PIPE)
		{
			dup2(tube[1], STDOUT_FILENO);
			close(tube[0]);
			close(tube[1]);
		}
		// TODO multiplos REDI_IN
		if (cmd->m_lst->matrix->head->rdrct == REDI_IN)
		{
			var.infile = ft_cpy_lst_to_array(cmd->m_lst->matrix->head->lst);
			ft_open_infile(var.infile);
			ft_remove_lst_front(cmd->m_lst->matrix);
		}
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

void	ft_execute_simple_cmd5(t_ast_node *cmd, t_mtrx_lst *env_list)
{
	t_var_exe	var;
	int			tube[2];

	if (cmd->m_lst->next->type == PIPE)
		pipe(tube);
	var.pid = fork();
	if (var.pid == 0)
	{
		if (cmd->m_lst->next->type == PIPE)
		{
			dup2(tube[1], STDOUT_FILENO);
			close(tube[0]);
			close(tube[1]);
		}
		if (cmd->m_lst->matrix->head->lst->head->type == REDI_IN)
		{
			ft_remove_lst_front(cmd->m_lst->matrix);
			var.infile = ft_cpy_lst_to_array(cmd->m_lst->matrix->head->lst);
			ft_open_infile(var.infile);
			ft_remove_lst_front(cmd->m_lst->matrix);
		}
		if (cmd->m_lst->matrix->last->prev->lst->head->type == REDI_OUT)
		{
			var.infile = ft_cpy_lst_to_array(cmd->m_lst->matrix->last->lst);
			ft_open_outfile(var.infile);
			ft_remove_list_back(cmd->m_lst->matrix);
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