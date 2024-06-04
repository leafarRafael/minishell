/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_oprtr_rdrct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:39:00 by tforster          #+#    #+#             */
/*   Updated: 2024/06/04 17:40:40 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"

static int	tkn_and_tkn(t_parse *parse, char *str, t_tkn_fc f1, t_tkn_fc f2);

int	tkn_is_oprtr(t_parse *parse)
{
	if (parse->type & (PIPE | AND_OP | OR_OP))
		return (1);
	return (0);
}

int	tkn_is_rdrct(t_parse *parse)
{
	if (parse->type & (REDI_IN | REDI_OUT | HERE_DOC | APPEND))
		return (1);
	return (0);
}

/**
 * @brief Syntax Check:
 * @note Check if after an OPRTR "|,||,&&" there is another OPRTR "|,||,&&"
 * @note Check if after an RDRCT  "<,>,<<,>>" there is another OPRTR "|,||,&&"
 * @note Check if after a RDRCT "<,>,<<,>>" there is another RDRCT "<,>,<<,>>"
*/
static int	tkn_and_tkn(t_parse *parse, char *str, t_tkn_fc f1, t_tkn_fc f2)
{
	if (parse->prev && f1(parse->prev) && f2(parse))
		return (syntax_error(parse, str, BAD_OPRTR_SYNTAX));
	return (NO_ERROR);
}

int	parse_oprtr(char *str, t_parse **parse, int *index)
{
	t_parse	*ptr;
	int		type;

	type = th_is_logical_oprtr(str, *index);
	ptr = parse_add_back(parse, parse_init(type, *index));
	ptr->size = 1;
	(*index)++;
	if (type & (OR_OP | AND_OP))
	{
		ptr->size++;
		(*index)++;
	}
	return (tkn_and_tkn(ptr, str, tkn_is_oprtr, tkn_is_oprtr)
		|| tkn_and_tkn(ptr, str, tkn_is_rdrct, tkn_is_oprtr));
}

int	parse_rdrct(char *str, t_parse **parse, int *index)
{
	t_parse	*ptr;
	int		type;

	type = th_is_io_rdrct(str, *index);
	ptr = parse_add_back(parse, parse_init(type, *index));
	ptr->size = 1;
	(*index)++;
	if (type & (HERE_DOC | APPEND))
	{
		ptr->size++;
		(*index)++;
	}
	return (tkn_and_tkn(ptr, str, tkn_is_rdrct, tkn_is_rdrct));
}
