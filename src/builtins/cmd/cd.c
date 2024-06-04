/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:21:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/04 07:44:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int exe_cd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
static void	setpwd(t_mlst *envlst);

void	cd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, ast, var);
	ft_valid_command_builtin(cmd, mini, ast, var);
	if (exe_cd(cmd, mini, ast, var))
		return ;
	finished_builtin(cmd, mini, ast, var);
}

static int exe_cd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->matrix->size == 1)
	{
		chdir(getenv("HOME"));
		setpwd(mini->m_lst_env);
		return (status_child = 0);
	}
	var->command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
	if (chdir(var->command_m[1]) < 0)
	{
		ft_msg_error(var->command_m[1], strerror(errno));
		ft_delcmtrx(var->command_m);
		return (status_child = 1);
	}
	setpwd(mini->m_lst_env);
	ft_delcmtrx(var->command_m);
	return (status_child = 0);
}

static void	setpwd(t_mlst *envlst)
{
	t_llst	*node;
	t_lst	*lst_pwd;
	char	*current_dir;
	char	buf[300];

	current_dir = getcwd(buf, 300);
	node = envlst->head;
	while(node->next != envlst->head)
	{
		if (!ft_strlstcmp(node->lst, "PWD=", 4))
		{
			while (node->lst->last->c != '=')
				lst_rmv_back(node->lst);
			while (*current_dir)
				ft_create_node_add_back(node->lst, *(current_dir++));
		}
		node = node->next;
	}
}
