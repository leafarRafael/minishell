/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/09 14:24:09 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_syntax.h"

static void	ft_execute_minishell(t_mini *mini);
int			g_status_child;

static void	init_minishell(t_mini *mini)
{
	mini->m_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	mini->color = ft_init_color();
	mini->collect = ft_init_collector();
	mini->collect_ast = ft_init_collector();
	mini->status = 0;
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
	builds_execution_call(mini);
	swap_tty(RESTORE, mini);
	ft_wait_execution(mini);
	ft_swap_environ(mini, RESTORE);
	ft_delete_mmlst(mini->mmlst);
}


