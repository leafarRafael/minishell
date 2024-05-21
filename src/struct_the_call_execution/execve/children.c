/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:19:18 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/21 17:54:05 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_expand_token(t_mlst *mlst);
static void	ft_valid_command(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
static void build_var_and_run_execve(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var);
static void	token_expand(t_mlst *mlst, t_llst *llist);

void	children(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	rl_clear_history();
	ft_expand_token(cmd->m_lst->matrix);
	ft_remove_quote_m_lst(cmd->m_lst->matrix);
	ft_manager_fd(cmd, mini, ast, var);

	// CHECK BUILT IN
	cmd->how_to_exe = ft_valid_builtin(cmd, mini, ast, var);
	if (cmd->how_to_exe == 0)
		ft_valid_command(cmd, mini, ast, var);
	ft_putstr_fd("\nTHE BUILTIN IS [", 2);
	ft_putnbr_fd(cmd->how_to_exe, 2);
	ft_putstr_fd("]\nEND\n", 2);
	// END

	build_var_and_run_execve(cmd, mini, ast, var);
}

static void build_var_and_run_execve(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{

	// PRINT THE COMMAND TO BE EXECUTED
	ft_putstr_fd("PRINT THE COMMAND TO BE EXECUTED\n", 2);
	ft_putstr_fd(var->command_m[0], 2);
	ft_putstr_fd("\nEND\n", 2);
	// END

	if (cmd->how_to_exe == 0)
	{
		var->env = ft_path_env(mini->m_lst_env);
		var->command_m = ft_cpy_mtrllst_to_cmtrx(cmd->m_lst->matrix);
		var->path_exe = ft_get_executable(mini, var, ast);
		if (execve(var->path_exe, &var->command_m[0], var->env) < 0)
			perror(var->path_exe);
	}
	// THIS IS THE BUILT IN
	else
	{
		if (cmd->how_to_exe == 2)
			ft_env(mini);
		else
			ft_putstr_fd("SOME OTHER BUILTIN\n", 2);
	}
	// END
	free_memory(mini, var, ast, 1);
}

static void	ft_valid_command(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	if (cmd->m_lst->matrix->size == 1 && cmd->m_lst->matrix->head->lst->size == 0)
	{
		ft_msg_error("''", " command not found");
		free_memory(mini, var, ast, 126);
	}
}

static void ft_manager_fd(t_ast_n *cmd, t_mini *mini, t_ast *ast, t_var_exe *var)
{
	close (mini->fd_std[0]);
	close (mini->fd_std[1]);
	if (cmd->m_lst->next->type == PIPE)
	{
		dup2(var->tube[1], STDOUT_FILENO);
		close(var->tube[0]);
		close(var->tube[1]);
	}
	if (ft_redirect(cmd->m_lst->matrix) < 0)
		free_memory(mini, var, ast, 1);
}

static void	ft_expand_token(t_mlst *mlst)
{
	t_var_matrix	v;
	t_mlst			*new_token;

	if (!mlst)
		return ;
	if (mlst->size == 1)
	{
		ft_expander_lst_token(mlst->head->lst);
		token_expand(mlst, mlst->head);
	}
	else
	{
		v.current_lst = mlst->head;
		v.next_lst = v.current_lst->next;
		v.i = 1;
		while (v.i <= mlst->size)
		{
			ft_expander_lst_token(v.current_lst->lst);
			token_expand(mlst, v.current_lst);
			v.current_lst = v.next_lst;
			v.next_lst = v.next_lst->next;
			v.i++;
		}
	}
}

static void	token_expand(t_mlst *mlst, t_llst *llist)
{
	t_mlst	*new_token;
	t_node	*node;
	int		i;

	if (llist->lst->head->type != D_QUOTES)
	{

		i = 1;
		node = llist->lst->head;
		while(i <= llist->lst->size)
		{
			if (node->c == 32)
				node->type = WH_SPACE;
			else
				node->type = NO_OP_TYPE;
			node = node->next;
			i++;
		}
		new_token = ft_token_cmd(llist->lst);
		insert_lnode_between(mlst, llist, new_token);
		free(new_token);
		ft_rmv_spcfc_lst_mtrx(mlst, llist);
	}
}
