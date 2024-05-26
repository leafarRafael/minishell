/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_oprtr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:39:00 by tforster          #+#    #+#             */
/*   Updated: 2024/05/25 19:43:57 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"
#include "th_syntax.h"

static int	syntax_oprtr(t_parse *parse, char *str);

int	token_is_oprtr(t_parse *parse)
{
	if (parse->type & (PIPE | AND_OP | OR_OP))
		return (1);
	return (0);
}

// Check if after an OPERATOR  "|, ||, &&" there is another OPERATOR "|, ||, &&"
static int	syntax_oprtr(t_parse *parse, char *str)
{
	if (parse->prev && token_is_oprtr(parse->prev) && token_is_oprtr(parse))
		return (th_syntax_error(parse, str, BAD_OPRTR_SYNTAX));
	return (NO_ERROR);
}

// Check if after an REDIRECT  "< , >, <<, >>" there is another OPERATOR "|, ||, &&"
static int	syntax_rdrct_oprtr(t_parse *parse, char *str)
{
	if (parse->prev && token_is_rdrct(parse->prev) && token_is_oprtr(parse))
		return (th_syntax_error(parse, str, MSSNG_FILE));
	return (NO_ERROR);
}

int	parse_oprtr(char *str, t_parse **parse, int *index)
{
	t_parse	*ptr;
	int		type;

	type = th_is_logical_oprtr(str, *index);
	ptr = parse_add_back(parse, parse_new(type, *index));
	ptr->size = 1;
	(*index)++;
	if (type & (OR_OP | AND_OP))
	{
		ptr->size++;
		(*index)++;
	}
	return(syntax_oprtr(ptr, str) || syntax_rdrct_oprtr(ptr, str));
}
