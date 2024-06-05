/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/05 16:13:59 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_syntax.h"

static void	ft_execute_minishell(t_mini *mini);
void		ft_scanner_env(t_mlst *mlst);
int			g_status_child;

// ARRUMAR PASTA /TEMP

int	main(void)
{
	t_mini	mini;
	char	*name;
	int		i;
	t_stx	stx;
	int		index;

	mini.m_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	mini.color = ft_init_color();
	i = 1;
	mini.status = 0;
	index = 0;
	while (index < 40)
	{
		mini.ast[index] = NULL;
		index++;
	}
	swap_tty(COPY, &mini);
	while (1)
	{
		ft_scanner_env(mini.m_lst_env);
		name = ft_get_program_name();
		ft_putstr_fd(name, 2);
		free(name);
		mini.input = readline(GRN " \033[1m\nminishel \u279C : \033[0m" RST);
		if (!mini.input)
			break ;
		add_history(mini.input);
		stx.error = th_parse_param(mini.input);
		if (!stx.error)
		{
			ft_putstr_fd(mini.color[i], 2);
			// if (!ft_input_is_valid(mini.input))
				ft_execute_minishell(&mini);
			i++;
			if (i == 6)
				i = 1;
			ft_putstr_fd(RESET, 2);
		}
		index = 0;
		while (mini.ast[index] && index < 40)
		{
			ft_delete_tree(mini.ast[index]);
			mini.ast[index] = NULL;
			index++;
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
		ft_scanner_equal(node->lst);
		node = node->next;
		i++;
	}
}
