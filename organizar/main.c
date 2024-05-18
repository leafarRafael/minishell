/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/18 13:12:35 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_define_node_tree(t_ast *ast);
static int	ft_valid_syntax_open_here_doc(t_lst *lst);
static int	*ft_init_ctrl_name(void);
static void	close_fd(t_mini *mini);
static void swap_tty(int copy_restore, t_mini *mini);

int status_child;

int	main(void)
{
	t_mini	mini;
	char	*input;
	char	**temp_environ;
	t_lst	*new_lst;

	temp_environ = __environ;
	mini.m_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	mini.env = ft_cpy_mtrllst_to_cmtrx(mini.m_lst_env);
	__environ = mini.env;
	while (1)
	{
		input = readline("minishell ~:");
		if (!input)
			break ;
		if (!ft_exit(input))
			break ;
		if (!ft_input_is_valid(input))
		{
			add_history(input);
			__environ = mini.env;
			mini.input_lst = ft_init_lst();
			mini.mmlst = init_mmlst();
			ft_add_string_in_list(mini.input_lst, input);
			ft_scanner_input(mini.input_lst);
			ft_valid_syntax_open_here_doc(mini.input_lst);
			swap_tty(COPY, &mini);
			ft_parse_exe(mini.input_lst, &mini);
			swap_tty(RESTORE, &mini);
			__environ = temp_environ;
			ft_delete_mmlst(mini.mmlst);
		}
	}
	rl_clear_history();
	close_fd(&mini);
	ft_delete_cmatrix(mini.env);
	ft_delete_matrix(mini.m_lst_env);
}

void	ft_parse_exe(t_lst *input, t_mini *mini)
{
	t_ast		*ast;

	ast = ft_init_ast();
	while (input->size > 0)
		ft_mmlst_add_back(mini->mmlst, ft_token_cmd(input));
	if (input)
	{
		free(input);
		input = NULL;
	}
	ft_define_cmd_status(mini->mmlst);
	ft_remove_cmd_status(mini->mmlst);
	ft_define_ast(ast, mini->mmlst);
	ft_execute(ast->root, mini, ast);
	ft_delete_tree(ast);
}

static int ft_valid_syntax_open_here_doc(t_lst *lst)
{
	t_node		*nd;
	int			*hdoc_ctrlname;
	int			i;

	hdoc_ctrlname = ft_init_ctrl_name();
	i = 1;
	nd = lst->head;
	while (nd->next != lst->head)
	{
		if (nd->type == HERE_DOC)
		{
			ft_finished_hdoc(lst, nd, hdoc_ctrlname);
			nd = lst->head;
		}
		nd = nd->next;
	}
	ft_scanner_input(lst);
	free(hdoc_ctrlname);
	return (-1);
}

static int	*ft_init_ctrl_name(void)
{
	int	*hdoc_ctrlname;

	hdoc_ctrlname = malloc(sizeof(int) * 4);
	hdoc_ctrlname[UNIT] = 0;
	hdoc_ctrlname[TEN] = 0;
	hdoc_ctrlname[HUNDRED] = 0;
	hdoc_ctrlname[THOUSAND] = 0;
	return (hdoc_ctrlname);
}

static void close_fd(t_mini *mini)
{
	close(mini->fd_std[0]);
	close(mini->fd_std[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

static void swap_tty(int copy_restore, t_mini *mini)
{
	if (copy_restore == COPY)
	{
		mini->fd_std[0] = dup(STDIN_FILENO);
		mini->fd_std[1] = dup(STDOUT_FILENO);
	}
	if (copy_restore == RESTORE)
	{
		dup2(mini->fd_std[0], STDIN_FILENO);
		dup2(mini->fd_std[1], STDOUT_FILENO);
		close(mini->fd_std[0]);
		close(mini->fd_std[1]);
	}
}