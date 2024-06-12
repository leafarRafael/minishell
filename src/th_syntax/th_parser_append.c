/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:07:47 by tforster          #+#    #+#             */
/*   Updated: 2024/06/12 14:28:00 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"

/**
 * @brief Syntax Check:
 * @note Check if after a OPEN PRNTHS "(" there is an OPERATOR "|, ||, &&". *
 * @note The check is done at the end of the append sub-parse.
*/
int	append_sub(char *str, t_parse *parse, int *index, t_parse_func parse_func)
{
	t_parse	*last;
	int		status;
	int		size;

	status = parse_func(str, &parse->sub, index);
	(*index)--;
	last = parse_last(parse->sub);
	size = 2 * ((last->type & (OPEN_PAREN | D_QUOTES | S_QUOTES)) > 0);
	parse->size += size + last->size;
	if (token_aft_opn_prnth(parse))
		return (syntax_error(parse, str, TKN_AFT_OPN_PRNTH));
	return (status);
}

t_parse	*parse_pop(t_parse *pop_node)
{
	t_parse	*prev;
	t_parse	*next;

	prev = pop_node->prev;
	next = pop_node->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	pop_node->prev = NULL;
	pop_node->next = NULL;
	return (pop_node);
}

t_parse	*parse_sub_last(t_parse *parse)
{
	t_parse	*last;

	last = parse;
	if (!last)
		return (NULL);
	while (last->sub)
		last = last->sub;
	return (last);
}
