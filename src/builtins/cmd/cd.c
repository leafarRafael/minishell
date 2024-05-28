/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:21:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/28 14:28:48 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void build_var_exe(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
static void	getpwd(t_mlst *envlst);
static void	ft_valid_command(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
static int	ft_find_str_inlist2(t_lst *lst, char *str, int size);

void	cd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	t_llst	*line;
	int		i;
	int		i_color;

	ft_manager_fd(cmd, mini, ast, var);
	build_var_exe(cmd, mini, ast, var);
	if (cmd->m_lst->next->type == PIPE || cmd->m_lst->prev->type == PIPE)
	{
		close (mini->fd_std[0]);
		close (mini->fd_std[1]);
		status_child = 0;
		free_memory(mini, var, ast, status_child);
	}
}

void build_var_exe(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	var->command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
	chdir(var->command_m[1]);
	getpwd(mini->m_lst_env);
}

static void	getpwd(t_mlst *envlst)
{
	t_llst	*node;
	t_lst	*lst_pwd;
	char	*current_dir;
	char	buf[300];

	current_dir = getcwd(buf, 300);
	node = envlst->head;
	while(node->next != envlst->head)
	{
		if (!ft_find_str_inlist2(node->lst, "PWD=", 4))
		{
			while (node->lst->last->c != '=')
				lst_rmv_back(node->lst);
			while (*current_dir)
				ft_create_node_add_back(node->lst, *(current_dir++));
		}
		node = node->next;
	}
}

static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[1], STDOUT_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
	if (ft_redirect_manager(cmd->m_lst->matrix) < 0)
		free_memory(mini, var, ast, 1);
}

static int	ft_find_str_inlist2(t_lst *lst, char *str, int size)
{
	t_var	v;
	char	*new;
	int		i;

	i = 0;
	new = ft_cpy_lst_to_array(lst);
	i = memcmp(str, new, size);
	free(new);
	return (i);
}