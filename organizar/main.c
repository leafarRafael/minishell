/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/13 18:18:23 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_define_node_tree(t_ast *ast);


static void	ft_change_name_file(int *number, t_lst *here_doc);
static void ft_finished_hdoc(t_lst *lst, t_node *nd, int *number);
static int ft_valid_syntax_open_here_doc(t_lst *lst);
static void	ft_replace_lst(t_lst *lst, t_lst *temp, char *env);

int	main(void)
{
	t_mini	mini;
	char	**temp_environ;
	t_lst	*new_lst;


	temp_environ = __environ;
	mini.m_lst_env = ft_cmtrix_to_mtrx_lst(__environ);
	mini.env = ft_cpy_mtrllst_to_cmtrx(mini.m_lst_env);
	__environ = mini.env;
	mini.fd_std[0] = dup(STDIN_FILENO);
	mini.fd_std[1] = dup(STDOUT_FILENO);
	while (1)
	{
		mini.input = readline("minishell ~:");
		if (!ft_exit(mini.input))
			break ;
		if (!ft_input_is_valid(mini.input))
		{
			__environ = mini.env;
			mini.input_lst = ft_init_lst();
			ft_add_string_in_list(mini.input_lst, mini.input);
			free(mini.input);
			ft_scanner_input(mini.input_lst);
			ft_valid_syntax_open_here_doc(mini.input_lst);
/* 
			mini.mmlst = init_mmlst();
			while (mini.input_lst->size > 0)
				ft_mmlst_add_back(mini.mmlst, ft_token_cmd(mini.input_lst));
			ft_parse_exe(mini.input_lst, &mini);
			ft_delete_mmlst(mini.mmlst);
			dup2(mini.fd_std[0], STDIN_FILENO);
			dup2(mini.fd_std[1], STDOUT_FILENO);
			close(mini.fd_std[0]);
			close(mini.fd_std[1]);
			__environ = temp_environ; */
		}
	}
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
	int			*number;
	int			i;

	number = malloc (sizeof(int) * 6);
	number[UNIT] = 0;
	number[TEN] = 0;
	number[HUNDRED] = 0;
	number[THOUSAND] = 0;
	i = 1;
	nd = lst->head;
	while (i <= lst->size)
	{
		if (nd->type == HERE_DOC)
			ft_finished_hdoc(lst, nd, number);
		nd = nd->next;
		i++;
	}
	ft_scanner_input(lst);
	return (-1);
}

static void ft_finished_hdoc(t_lst *lst, t_node *nd, int *number)
{
	t_lst	*here_doc;
	t_node	*tn;
	t_node	*next;
	t_node	*prev;
	t_node	*tmp_nd;
	t_lst	temp_lst;
	int		size;
	int		is_head;
	int		is_last;

	is_head = 0;
	is_last = 0;
	here_doc = ft_init_lst();
	ft_add_string_in_list(here_doc, PATH_HERE_DOC);
	size = 0;
	tmp_nd = nd;
	while (tmp_nd->type == HERE_DOC)
	{
		tmp_nd->type = NO_OP_TYPE;
		tmp_nd = tmp_nd->next;
		size++;
	}
	while (tmp_nd->type == WH_SPACE)
	{
		tmp_nd = tmp_nd->next;
		size++;
	}
	while (tmp_nd->type != WH_SPACE && tmp_nd != lst->head)
	{
		tmp_nd = tmp_nd->next;
		size++;
	}
	tmp_nd = tmp_nd->prev;
	if (nd == lst->head)
		is_head++;
	if (tmp_nd == lst->last)
		is_last++;
	temp_lst.head = nd;
	temp_lst.last = tmp_nd;
	temp_lst.size = size;
	ft_change_name_file(number, here_doc);
	tn = nd->next;
	next = tmp_nd->next;
	prev = nd->prev;
	while (nd != tmp_nd)
	{
		ft_remove_specific_node(lst, nd);
		nd = tn;
		tn = tn->next;
	}
	ft_remove_specific_node(lst, nd);
	prev->next = next;
	next->prev = prev;
	ft_lst_btwn_lst(lst, prev, next, here_doc);
	if (is_head > 0)
		lst->head = here_doc->head;
	if (is_last > 0)
		lst->last = here_doc->last;
	ft_putlst_fd(lst, 1 ,2);
	free(here_doc);
	write(2, "\n", 1);
}

static void	ft_change_name_file(int *number, t_lst *here_doc)
{
	here_doc->last->c += number[UNIT];
	here_doc->last->prev->c += number[TEN];
	here_doc->last->prev->prev->c += number[HUNDRED];
	here_doc->last->prev->prev->prev->c += number[THOUSAND];
	number[UNIT]++;
	if (number[UNIT] > 9)
	{
		number[UNIT] = 0;
		number[TEN]++;
	}
	if (number[TEN] > 9)
	{
		number[TEN] = 0;
		number[HUNDRED]++;
	}
	if (number[HUNDRED] > 9)
	{
		number[HUNDRED] = 0;
		number[THOUSAND]++;
	}
}