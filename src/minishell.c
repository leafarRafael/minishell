/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/11 11:56:18 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termio.h>
#include "minishell.h"
#include "mini_utils.h"
#include "th_syntax.h"
#include "sigaction.h"

static void	ft_execute_minishell(t_mini *mini);
static void	ft_call_wait(t_mini *mini);
int			g_status_child;

int	main(void)
{
	t_mini				mini;
	struct termios		fd;

	fd = (struct termios){0};
	init_minishell(&mini);
	tcgetattr(STDIN_FILENO, &fd);
	while (1)
	{
		init_signal();
		swap_tty(RESTORE, &mini);
		ft_scanner_env(mini.m_lst_env);
		print_pwd();
		mini.input = readline("\nminishell$: ");
		if (!mini.input)
			mini.input = sig_eof(mini.input);
		mini.status = ft_input_is_valid(mini.input);
		ft_putstr_fd(mini.color[mini.i_color++], 2);
		if (!mini.status)
			ft_execute_minishell(&mini);
		if (mini.i_color == 6)
			mini.i_color = 0;
		ft_putstr_fd(RESET, 2);
		tcsetattr(STDIN_FILENO, TCSANOW, &fd);
	}
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
	ft_call_wait(mini);
}

static void	ft_call_wait(t_mini *mini)
{
	if (g_status_child != 99)
		builds_execution_call(mini);
	else
	{
		swap_tty(RESTORE, mini);
		ft_wait_execution(mini);
		ft_swap_environ(mini, RESTORE);
		if (mini->mmlst)
			ft_delete_mmlst(mini->mmlst);
		g_status_child = 130;
		return ;
	}
	swap_tty(RESTORE, mini);
	ft_wait_execution(mini);
	ft_swap_environ(mini, RESTORE);
	if (mini->mmlst)
		ft_delete_mmlst(mini->mmlst);
}
