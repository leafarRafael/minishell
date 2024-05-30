/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_open_prnth.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:58:34 by tforster          #+#    #+#             */
/*   Updated: 2024/05/28 18:27:35 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"
#include "th_syntax.h"

static int	token_bfr_opn_prnth(t_parse *parse);

int	parse_bfr_fst_prnth(t_parse **parse, char *str, int *index)
{
	if (token_bfr_opn_prnth(*parse))
		return (syntax_error(parse_last(*parse), str, TKN_BFR_OPN_PRNTH));
	return (parse_prnth(str, parse, index));
}

int	parse_bfr_sub_prnth(t_parse *parse, char *str, int *index)
{
	if (token_bfr_opn_prnth(parse->sub))
		return (syntax_error(parse_last(parse->sub), str, TKN_BFR_OPN_PRNTH));
	return (append_sub(str, parse, index, parse_prnth));
}

// Check if after a CLOSE PARENTHESIS ")" there is a OPEN PARENTHESIS "("
// Check if after a COMMAND "text" there is a OPEN PARENTHESIS "("
// Check if after a REDIRECT  "< , >, <<, >>" there is a OPEN PARENTHESIS "("
static int	token_bfr_opn_prnth(t_parse *parse)
{
	int	type;

	type = (OPEN_PAREN | COMMAND | D_QUOTES | S_QUOTES
			| REDI_IN | REDI_OUT | HERE_DOC | APPEND);
	if (parse && (parse_last(parse)->type & type))
		return (1);
	return (0);
}

// Check if after a OPEN PARENTHESIS "(" there is an OPERATOR "|, ||, &&"
int	token_aft_opn_prnth(t_parse *parse)
{
	if (parse->type == OPEN_PAREN && tkn_is_oprtr(parse->sub))
		return (1);
	return (0);
}
