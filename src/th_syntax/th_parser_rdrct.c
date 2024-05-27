/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_rdrct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:40:48 by tforster          #+#    #+#             */
/*   Updated: 2024/05/27 18:12:49 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"
#include "th_syntax.h"

int	token_is_rdrct(t_parse *parse)
{
	if (parse->type & (REDI_IN | REDI_OUT | HERE_DOC | APPEND))
		return (1);
	return (0);
}

// Check if after a REDIRECT "< , >, <<, >>" there is another REDIRECT "< , >, <<, >>"
int	syntax_rdrct(t_parse *parse, char *str)
{
	if (parse->prev && token_is_rdrct(parse->prev) && token_is_rdrct(parse))
		return (syntax_error(parse, str, BAD_RDRTC_SYNTAX));
	return (NO_ERROR);
}

int	parse_rdrct(char *str, t_parse **parse, int *index)
{
	t_parse	*ptr;
	int		type;

	type = th_is_io_rdrct(str, *index);
	ptr = parse_add_back(parse, parse_new(type, *index));
	ptr->size = 1;
	(*index)++;
	if (type & (HERE_DOC |  APPEND))
	{
		ptr->size++;
		(*index)++;
	}
	return (syntax_rdrct(ptr, str));
}
