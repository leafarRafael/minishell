/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/07 19:23:34 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_syntax.h"

static void	ft_execute_minishell(t_mini *mini);
void		ft_scanner_env(t_mlst *mlst);
int			g_status_child;

static void	init_minishell(t_mini *mini)
{
	int		index;

	index = 0;
	mini->m_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	mini->color = ft_init_color();
	mini->status = 0;
	index = 0;
	while (index < 40)
	{
		mini->ast[index] = NULL;
		index++;
	}
	swap_tty(COPY, mini);
}

static void print_pwd()
{
	char	*name;

	name = NULL;
	name = ft_get_program_name();
	if (name)
	{
		ft_putstr_fd(name, 2);
		free(name);
	}
}

static void clear_garbage(t_mini *mini)
{
	int		index;

	index = 0;
	while (mini->ast[index] && index < 40)
	{
		ft_delete_tree(mini->ast[index]);
		mini->ast[index] = NULL;
		index++;
	}
}

int	main(void)
{
	t_mini				mini;
	int					index;
	struct sigaction	sa;

	sa.sa_handler  = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	printf("SIGQUIT is now ignored. Press Ctrl+\\ (backslash) to test it.\n");

	init_minishell(&mini);
	index = 1;
	while (1)
	{
		swap_tty(RESTORE, &mini);
		ft_scanner_env(mini.m_lst_env);
		print_pwd();
		mini.input = readline("\n minishell$ : ");
		if (!mini.input)
			break ;
		mini.status = ft_input_is_valid(mini.input);
		if (!mini.status)
		{
			ft_putstr_fd(mini.color[index], 2);
			ft_execute_minishell(&mini);
			index++;
			if (index == 6)
				index = 1;
			ft_putstr_fd(RESET, 2);
		}
		clear_garbage(&mini);
	}
	ft_delcmtrx(mini.color);
	rl_clear_history();
	close_allfd(&mini);
	ft_delete_matrix(mini.m_lst_env);
	return (g_status_child);
}

static void	ft_execute_minishell(t_mini *mini)
{
	ft_swap_environ(mini, SWAP);
	mini->input_lst = ft_init_lst();
	mini->mmlst = init_mmlst();
	ft_add_string_in_list(mini->input_lst, mini->input);
	free(mini->input);
	ft_scanner_input(mini->input_lst);
	ft_valid_syntax_open_here_doc(mini->input_lst);
	while (mini->input_lst->size > 0)
		ft_mmlst_add_back(mini->mmlst, ft_token_cmd(mini->input_lst));
	ft_delete_list(mini->input_lst);
	mini->pid = -42;
	builds_execution_call(mini);
	waitpid(mini->pid, &mini->status, 0);
	if (mini->pid != -42)
	{
		if (WIFSIGNALED(mini->status))
		{
			if (WTERMSIG(mini->status) == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", 2);
			g_status_child = 128 + WTERMSIG(mini->status);
		}
		else
			g_status_child = WEXITSTATUS(mini->status);
	}
	ft_swap_environ(mini, RESTORE);
	ft_delete_mmlst(mini->mmlst);
}

void	ft_scanner_env(t_mlst *mlst)
{
	t_llst	*node;
	int		i;

	node = mlst->head;
	i = 0;
	while (i < mlst->size)
	{
		ft_scanner_input(node->lst);
		node = node->next;
		i++;
	}
}
