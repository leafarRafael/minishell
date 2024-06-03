/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:07:47 by tforster          #+#    #+#             */
/*   Updated: 2024/06/03 20:22:30 by tforster         ###   ########.fr       */
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
	t_parse	*sub;
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
