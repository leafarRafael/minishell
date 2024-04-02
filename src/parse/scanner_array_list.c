/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_array_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:30:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/02 15:36:51 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_composite_type(char current_c, char next_c);
static int	is_simple_type(char current_c);
static int	ft_size_two_less(t_lst *lst);

void	ft_scanner_input(t_lst *lst)
{
	t_var	var;
	int		type;
	int		quotes;

	quotes = 0;
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
			if (var.temp_node->c == _SINGLE_QUOTES_ || var.temp_node->c == _DOUBLE_QUOTES_)
			{
				if (quotes == 1)
					quotes--;
				else
					quotes++;
			}
			var.temp_node->type = is_simple_type(var.temp_node->c);
			if (quotes == 1)
				var.temp_node->type = NO_OPERATOR_TYPE;
			type = ft_is_composite_type(var.temp_node->c, var.temp_node->next->c);
			if (type != -1 && var.temp_node != lst->last)
			{
				if (quotes != 0)
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
	if (current_c == _SINGLE_QUOTES_)
		return (SINGLE_QUOTES);
	if (current_c == _DOUBLE_QUOTES_)
		return (DOUBLE_QUOTES);
	if (current_c == _DOLLAR_SING_)
		return (DOLLAR_SIGN);
	if (current_c == _REDI_INFILE_)
		return (REDI_INFILE);
	if (current_c == _REDIRECT_)
		return (REDIRECT);
	if (current_c == _LEFT_PAREN_)
		return (LEFT_PAREN);
	if (current_c == _RIGHT_PAREN_)
		return (RIGHT_PAREN);
	if (current_c == _PIPE_LINE_)
		return (PIPE);
	if (_WHITE_SPACE_(current_c))
		return (WHITE_SPACE);
	return (NO_OPERATOR_TYPE);
}

static int	ft_is_composite_type(char current_c, char next_c)
{
	if (_HERE_DOC_(current_c, next_c))
		return (HERE_DOC);
	if (_APPEND_(current_c, next_c))
		return (APPEND);
	if (_AND_(current_c, next_c))
		return (AND);
	if (_OR_(current_c, next_c))
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

void	ft_scanner_input_2(t_lst *lst)
{
	t_var	var;
	int		type;
	int		quotes;

	quotes = 0;
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
			if (var.temp_node->c == _SINGLE_QUOTES_)
			{
				if (quotes == 1)
					quotes--;
				else
					quotes++;
			}
			var.temp_node->type = is_simple_type(var.temp_node->c);
			if (quotes == 1)
			{
				if (var.temp_node->type != SINGLE_QUOTES)
					var.temp_node->type = NO_OPERATOR_TYPE;
			}
			type = ft_is_composite_type(var.temp_node->c, var.temp_node->next->c);
			if (type != -1 && var.temp_node != lst->last)
			{
				if (quotes != 0)
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