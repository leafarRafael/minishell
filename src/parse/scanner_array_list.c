/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_array_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:30:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/04 17:46:37 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_composite_type(char current_c, char next_c);
static int	is_simple_type(char current_c);
static int	ft_size_two_less(t_lst *lst);
static void	ft_is_quotes(int *i);

void	ft_scanner_input(t_lst *lst)
{
	t_var	var;
	int		type;
	int		s_quotes;
	int		d_quotes;

	d_quotes = 0;
	s_quotes = 0;
	if (!lst)
		return ;
	if (!lst->head || !lst->last)
		return ;
	if (!ft_size_two_less(lst))
		return ;
	var.i = 0;
	if (lst->size > 2)
	{
		var.temp_node = lst->head;
		while (var.i <= lst->size )
		{
			type = -1;
			var.temp_node->type = is_simple_type(var.temp_node->c);
			type = ft_is_composite_type(var.temp_node->c, var.temp_node->next->c);
			if (is_simple_quotes(var.temp_node->c) && d_quotes == 0)
				ft_is_quotes(&s_quotes);
			if (is_double_quotes(var.temp_node->c) && s_quotes == 0)
				ft_is_quotes(&d_quotes);
			if (s_quotes == 1 && !is_simple_quotes(var.temp_node->c))
				var.temp_node->type = NO_OPERATOR_TYPE;
			if (d_quotes == 1 && !is_double_quotes(var.temp_node->c) && !is_dollar(var.temp_node->c))
				var.temp_node->type = NO_OPERATOR_TYPE;
			if (type != -1 && var.temp_node != lst->last)
			{
				if (s_quotes != 0 || d_quotes != 0)
					type = NO_OPERATOR_TYPE;
				var.temp_node->type = type;
				var.temp_node->next->type = type;
				var.temp_node = var.temp_node->next;
				var.i++;
			}
			var.temp_node = var.temp_node->next;
			var.i++;
		}
	}
}

static int	is_simple_type(char current_c)
{
	if (is_simple_quotes(current_c))
		return (SINGLE_QUOTES);
	if (is_double_quotes(current_c))
		return (DOUBLE_QUOTES);
	if (is_dollar(current_c))
		return (DOLLAR_SIGN);
	if (ft_is_infile(current_c))
		return (REDI_INFILE);
	if (ft_is_outfile(current_c))
		return (REDIRECT);
	if (is_open_parenthesis(current_c))
		return (OPEN_PAREN);
	if (is_close_parenthesis(current_c))
		return (CLOSE_PAREN);
	if (is_pipe(current_c))
		return (PIPE);
	if (is_white_space(current_c) || is_tab_character(current_c))
		return (WHITE_SPACE);
	return (NO_OPERATOR_TYPE);
}

static int	ft_is_composite_type(char current_c, char next_c)
{
	if (ft_is_here_doc(current_c, next_c))
		return (HERE_DOC);
	if (ft_is_append(current_c, next_c))
		return (APPEND);
	if (ft_is_and(current_c, next_c))
		return (AND);
	if (ft_is_or(current_c, next_c))
		return (OR);
	return (-1);
}

static int	ft_size_two_less(t_lst *lst)
{
	int type;

	if (lst->size == 1)
	{
		lst->head->type = is_simple_type(lst->head->c);
		return (0);
	}
	if (lst->size == 2)
	{
		type = -1;
		type = ft_is_composite_type(lst->head->c, lst->last->c);
		if (type != -1)
		{
			lst->head->type = type;
			lst->last->type = type;
		}
		else
		{
			lst->head->type = is_simple_type(lst->head->c);
			lst->last->type = is_simple_type(lst->last->c);
		}
		return (0);
	}
	return (-1);
}

static void	ft_is_quotes(int *i)
{
	if ((*i) == 1)
		(*i)--;
	else
		(*i)++;
}