/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_prnth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:58:34 by tforster          #+#    #+#             */
/*   Updated: 2024/05/27 19:41:38 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"
#include "th_syntax.h"

static int token_bfr_opn_prnth(t_parse *parse);
static int syntax_cmd_opn_prnth(t_parse *parse, char *str);
static int syntax_rdrct_opn_prnth(t_parse *parse, char *str);
static int syntax_prnth_opn_prnth(t_parse *parse, char *str);

int	parse_bfr_fst_prnth(t_parse **parse, char *str, int *index)
{
	if (token_bfr_opn_prnth(*parse))
		return (syntax_error(parse_last(*parse), str, STX_IN_TOKEN));
	return (parse_prnth(str, parse, index));
}

int	parse_bfr_sub_prnth(t_parse *parse, char *str, int *index)
{

	if (token_bfr_opn_prnth(parse->sub))
		return (syntax_error(parse_last(parse->sub), str, STX_IN_TOKEN));
	return (append_sub(str, parse, index, parse_prnth));
}

// Check if after a CLOSE PARENTHESIS ")" there is a OPEN PARENTHESIS "("
// Check if after a COMMAND "text" there is a OPEN PARENTHESIS "("
// Check if after a REDIRECT  "< , >, <<, >>" there is a OPEN PARENTHESIS "("
static int token_bfr_opn_prnth(t_parse *parse)
{
	int	type;

	type = (OPEN_PAREN | COMMAND | D_QUOTES | S_QUOTES | REDI_IN | REDI_OUT | HERE_DOC | APPEND);
	if (parse && (parse_last(parse)->type & type))
		return(1);
	return (0);
}

// Check if after a CLOSE PARENTHESIS ")" there is a OPEN PARENTHESIS "("
int syntax_prnth_opn_prnth(t_parse *parse, char *str)
{
	if (parse && (parse_last(parse)->type & OPEN_PAREN))
		return(1);
	return (0);

}

// Check if after a COMMAND "text" there is a OPEN PARENTHESIS "("
static int syntax_cmd_opn_prnth(t_parse *parse, char *str)
{
	if (parse && (parse_last(parse)->type & (COMMAND | D_QUOTES | S_QUOTES)))
		return (1);
	return (0);

}

// Check if after a REDIRECT  "< , >, <<, >>" there is a OPEN PARENTHESIS "("
static int syntax_rdrct_opn_prnth(t_parse *parse, char *str)
{
	if (parse && (parse_last(parse)->type & (REDI_IN | REDI_OUT | HERE_DOC | APPEND)))
		return (1);
	return (0);
}
