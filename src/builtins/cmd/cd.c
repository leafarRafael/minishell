/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:21:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/05 12:17:31 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	exe_cd(t_ast_n *cmd, t_mini *mini, t_var_exe *var);
static void	setpwd(t_mlst *envlst);

void	cd(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, var);
	ft_valid_command_builtin(cmd);
	if (exe_cd(cmd, mini, var))
	{
		finished_builtin(cmd, mini, var);
		return ;
	}
	finished_builtin(cmd, mini, var);
}

static int	exe_cd(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	g_status_child = 0;
	if (cmd->m_lst->matrix->size == 1)
	{
		chdir(getenv("HOME"));
		setpwd(mini->m_lst_env);
		return (g_status_child);
	}
	var->command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
	if (chdir(var->command_m[1]) < 0)
	{
		ft_msg_error(var->command_m[1], strerror(errno));
		ft_delcmtrx(var->command_m);
		var->command_m = NULL;
		g_status_child = 1;
		return (g_status_child);
	}
	setpwd(mini->m_lst_env);
	ft_delcmtrx(var->command_m);
	var->command_m = NULL;
	return (g_status_child);
}

static void	setpwd(t_mlst *envlst)
{
	t_llst	*env;
	char	*current_dir;
	char	buf[300];
	char	*prefix;

	current_dir = getcwd(buf, 300);
	env = envlst->head;
	while (env->next != envlst->head)
	{
		prefix = get_prfx(find_type_rtrn_ptr(env->lst, EQUAL_SING), env->lst);
		if (!ft_strncmp("PWD", prefix, ft_strlen(prefix) + 1))
		{
			while (env->lst->last->c != '=')
				lst_rmv_back(env->lst);
			while (*current_dir)
				ft_create_node_add_back(env->lst, *(current_dir++));
		}
		free(prefix);
		env = env->next;
	}
}
