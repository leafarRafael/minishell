/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/26 18:02:22 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_simple_cmd2(t_ast_node *cmd, t_mtrx_lst *env_list);
void	ft_execute_simple_cmd3(t_ast_node *cmd, t_mtrx_lst *env_list);
char	*ft_get_executable2(char *command, char **path);
void	ft_execute_tree(t_ast_node *root, t_mtrx_mtrx *mtrx_mtrx, t_mtrx_lst *env);

int main()
{
	t_var_minishell v;
	char			**env;

	v.looping_shell = 1;
	env = NULL;
	v.temp__environ = __environ;
	v.mrtx_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	v.env = ft_cpy_mtrllst_to_cmtrx(v.mrtx_lst_env);
	while (v.looping_shell)
	{
		v.infile = readline("minishell ~:");
		if (!ft_input_is_valid(v.infile))
		{
			__environ = v.env;
			v.input_user = ft_init_lst();
			v.list_matrix = ft_mtrx_mtrx_lst();
			ft_add_string_in_list(v.input_user, v.infile);
			ft_scanner_input(v.input_user);
			while (v.input_user->size > 0)
				ft_create_node_matrix_add_back(v.list_matrix, ft_simple_comand(v.input_user));
			ft_print_todos_os_tokens_expandidos(v.list_matrix);
			ft_define_cmd_operator(v.list_matrix);
			ft_valid_op_in_subshell(v.list_matrix);
			v.ast = ft_init_ast();
			ft_populetree(v.ast, v.list_matrix);
			ft_execute_tree(v.ast->root, v.list_matrix, v.mrtx_lst_env);
			ft_free_memory_revert_environ(&v);
		}
	}
	ft_delete_cmatrix(v.env);
	ft_delete_matrix(v.mrtx_lst_env);
}

void ft_execute_tree(t_ast_node *root, t_mtrx_mtrx *mtrx_mtrx, t_mtrx_lst *env)
{
	if (root != NULL)
	{
		ft_execute_tree(root->left, mtrx_mtrx, env);
		ft_execute_simple_cmd3(root, env);
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
		if (cmd->m_lst->matrix->last->prev->lst->head->type == REDIRECT)
		{
			var.outfile = ft_cpy_lst_to_array(cmd->m_lst->matrix->last->lst);
			ft_open_outfile(var.outfile);
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
		if (cmd->m_lst->next->type == REDIRECT)
			ft_open_outfile(var.command_m[i]);
		if (i > 0 )
			ft_remove_lst_front(cmd->m_lst->matrix);
		var.env = ft_path_env(env_list);
		var.path_exe = ft_get_executable(var.command_m[i], var.env);
		if (var.path_exe)
			execve(var.path_exe, &var.command_m[i], var.env);
		exit(1);
	}
}

char	*ft_get_executable2(char *command, char **path)
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
