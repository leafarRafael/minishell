/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/23 15:32:23 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execute_minishell(t_mini *mini);
int status_child;

int	main(void)
{
	t_mini	mini;

	mini.m_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	while (1)
	{
		status_child = 0;
		mini.input = readline("minishell ~:");
		if (!mini.input)
			break ;
		if (!ft_exit(mini.input))
			break ;
		if (!ft_input_is_valid(mini.input))
			ft_execute_minishell(&mini);
	}
	rl_clear_history();
	close_allfd(&mini);
	ft_delete_matrix(mini.m_lst_env);
	return (1);
}

static void	ft_execute_minishell(t_mini *mini)
{
	ft_swap_environ(mini, SWAP);
	add_history(mini->input);
	mini->input_lst = ft_init_lst();
	mini->mmlst = init_mmlst();
	ft_add_string_in_list(mini->input_lst, mini->input);
	free(mini->input);
	ft_scanner_input(mini->input_lst);
	ft_valid_syntax_open_here_doc(mini->input_lst);
	while (mini->input_lst->size > 0)
		ft_mmlst_add_back(mini->mmlst, ft_token_cmd(mini->input_lst));
	ft_delete_list(mini->input_lst);
	swap_tty(COPY, mini);
	builds_execution_call(mini->input_lst, mini);
	swap_tty(RESTORE, mini);
	ft_swap_environ(mini, RESTORE);
	ft_delete_mmlst(mini->mmlst);
}



