/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_close_prnth.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:44:38 by tforster          #+#    #+#             */
/*   Updated: 2024/05/30 16:42:15 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"
#include "th_syntax.h"

static int	token_bfr_cls_prnth(t_parse *parse);

// Check if there is an EMPTY PARENTHESIS "(...)"
int	parse_bfr_cls_prnth(t_parse *parse, char *str, int *index)
{
	if (token_bfr_cls_prnth(parse))
		return (syntax_error(parse_last(parse->sub), str, TKN_BFR_CLS_PRNTH));
	if (parse->sub == NULL)
		return (syntax_error(parse, str, EMPTY_PRNTH));
	(*index)++;
	return (NO_ERROR);
}

// Check if after an OPERATOR "|, ||, &&" there is CLOSE PARENTHESIS ")"
// Check if after a REDIRECT  "< , >, <<, >>" there is CLOSE PARENTHESIS ")"
static int	token_bfr_cls_prnth(t_parse *parse)
{
	if (parse->sub && (tkn_is_oprtr(parse_last(parse->sub))
			|| tkn_is_rdrct(parse_last(parse->sub))))
		return (1);
	return (0);
}
