/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:21:05 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/05 12:18:03 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	putpwd(t_mini *mini);

void	pwd(t_ast_n *cmd, t_mini *mini, t_var_exe *var)
{
	if (cmd->m_lst->prev->type == AND_OP && g_status_child != 0)
		return ;
	if (cmd->m_lst->prev->type == OR_OP && g_status_child == 0)
		return ;
	ft_manager_fd_builtin(cmd, mini, var);
	ft_valid_command_builtin(cmd);
	putpwd(mini);
	finished_builtin(cmd, mini, var);
}

static void	putpwd(t_mini *mini)
{
	t_llst	*env;
	char	*prefix;
	int		i;

	env = mini->m_lst_env->head;
	i = 0;
	while (i < mini->m_lst_env->size)
	{
		prefix = get_prfx(find_type_rtrn_ptr(env->lst, EQUAL_SING), env->lst);
		if (!ft_strncmp("PWD", prefix, ft_strlen(prefix) + 1))
		{
			ft_putstr_fd(mini->color[0], STDOUT_FILENO);
			ft_putlst_fd(env->lst, 1, STDOUT_FILENO);
			ft_putstr_fd(RESET, STDOUT_FILENO);
			free(prefix);
			break ;
		}
		free(prefix);
		env = env->next;
		i++;
	}
}
