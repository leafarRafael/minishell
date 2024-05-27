/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/27 13:06:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execute_minishell(t_mini *mini);
static void	getpwd(t_mlst *envlst);
int status_child;


int	main(void)
{
	t_mini	mini;
	char	*name;
	int		i;

	mini.color = ft_init_color();
	mini.m_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	i = 1;
	while (1)
	{
		name = ft_get_program_name();
		mini.input = readline(name);
		free(name);
		ft_putstr_fd(mini.color[i], 2);
		if (!mini.input)
			break ;
		if (!ft_exit(mini.input))
			break ;
		if (!ft_input_is_valid(mini.input))
			ft_execute_minishell(&mini);
		i++;
		if (i == 6)
			i = 1;
		ft_putstr_fd(RESET, 2);
	}
	rl_clear_history();
	close_allfd(&mini);
	ft_delcmtrx(mini.color);
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

static void	getpwd(t_mlst *envlst)
{
	t_llst	*node;
	t_lst	*lst_pwd;
	char	*current_dir;
	char	buf[300];

	current_dir = getcwd(buf, 300);
	lst_pwd = ft_init_lst();
	ft_add_string_in_list(lst_pwd, current_dir);
	ft_putlst_fd(lst_pwd, 1, 2);
	node = envlst->head;
	while(node->next != envlst->head)
	{
		if (ft_find_str_inlist(node->lst, "PWD", 3) != -1)
			ft_putlst_fd(node->lst, 1, 2);
		node = node->next;
	}
}

