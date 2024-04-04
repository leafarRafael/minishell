/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:31:51 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/04 17:13:19 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_find_and_expand(t_lst *lst, t_lst *dest);
static int	ft_find_dollar(t_lst *lst);
static int	ft_replace_content(t_lst *lst, t_lst *temp, char *env);

int	ft_expander_variable(t_matrix_lst *m_lst)
{
	t_variables_parse	var;
	int					have_many_dollar;

	have_many_dollar = 0;
	var.t_line = m_lst->head;
	var.lst_current = var.t_line->lst;
	var.index_matrix = 1;
	while (var.index_matrix <= m_lst->size)
	{
		var.temp_lst.size = 0;
		var.temp_lst.head = NULL;
		var.temp_lst.last = NULL;
		ft_scanner_input(var.lst_current);
		have_many_dollar = ft_find_dollar(var.lst_current);
		ft_find_and_expand(var.lst_current, &var.temp_lst);
		if (have_many_dollar > 0)
			var.lst_current = var.t_line->lst;
		else
		{
			var.lst_current = var.t_line->lst;
			var.t_line = var.t_line->next;
			var.lst_current = var.t_line->lst;
			var.index_matrix++;
		}	
	}
	return (0);
}

static int	ft_find_dollar(t_lst *lst)
{
	t_var	var;
	int		dollar;

	if (!lst)
		return (-1);
	if (lst->size == 0)
		return (-1);
	var.current_node = lst->head;
	var.i = 1;
	dollar = 0;
	while (var.i <= lst->size)
	{
		if (var.current_node->type == DOLLAR_SIGN)
			dollar++;
		var.current_node = var.current_node->next;
		var.i++;
	}
	return (dollar);
}

static void ft_find_and_expand(t_lst *lst, t_lst *dest)
{
	t_variables_parse	var;
	char *env;

	var.index_lst = 1;
	var.found = 0;
	var.current_node = lst->head;
	while (var.index_lst <= lst->size)
	{
		if (var.current_node->type == DOLLAR_SIGN)
		{
			var.found = 1;
			(*dest).head = var.current_node;
			var.current_node = var.current_node->next;
			var.index_lst++;
			(*dest).size++;
			while (var.index_lst <= lst->size && var.current_node->type == NO_OPERATOR_TYPE)
			{
				if (is_simple_quotes(var.current_node->c))
					break ;
				(*dest).last = var.current_node;
				var.current_node = var.current_node->next;
				var.index_lst++;
				(*dest).size++;
			}
		}
		if (var.found != 0)
			break ;
		var.current_node = var.current_node->next;
		var.index_lst++;
	}
	if (var.found != 0)
	{
		var.expand = ft_cpy_lst_to_array(dest);
		env = getenv(&var.expand[1]);
		ft_replace_content(lst, dest, env);
	}
}

static int	ft_replace_content(t_lst *lst, t_lst *temp, char *env)
{
	t_variables_parse	var;
	t_lst				*lst_temp;
	int					is_head;
	int					is_last;

	is_last = 0;
	is_head = 0;
	if (!lst || !temp)
		return (-1);
	var.current_node = temp->head;
	var.next_node = temp->head->next;
	if (!env)
	{
		while (temp->size > 0)
		{
			ft_remove_specific_node(lst, var.current_node);
			temp->size--;
			var.current_node = var.next_node;
			var.next_node = var.next_node->next;
		}
	}
	else
	{
		lst_temp = ft_init_lst();
		var.temp_lst.head = temp->head->prev;
		var.temp_lst.last = temp->last->next;
		if (lst->head == temp->head)
			is_head++;
		if (lst->last == temp->last)
			is_last++;
		while (temp->size > 0)
		{
			ft_remove_specific_node(lst, var.current_node);
			temp->size--;
			var.current_node = var.next_node;
			var.next_node = var.next_node->next;
		}
		ft_add_string_in_list(lst_temp, env);
		ft_insert_lst_between_lst(lst, var.temp_lst.head, var.temp_lst.last, lst_temp);
		if (is_head > 0)
			lst->head = lst_temp->head;
		if (is_last > 0)
			lst->last = lst_temp->last;
		free(lst_temp);
	}
}
