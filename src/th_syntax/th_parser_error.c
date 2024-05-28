/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:46:00 by tforster          #+#    #+#             */
/*   Updated: 2024/05/28 18:21:58 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"

static int	err_msg(char *msg1, char *msg2, t_sytx_er error);
static int	parse_err(t_parse *parse, char *str, t_sytx_er error);

int	syntax_error(t_parse *parse, char *str, t_sytx_er error)
{
	if (error == N_CLS_PRNTH)
		return (err_msg("no clossing", "PARENTHESIS", N_CLS_PRNTH));
	else if (error == N_OPN_PRNTH)
		return (err_msg("no opennig", "PARENTHESIS", N_OPN_PRNTH));
	else if (error == EMPTY_PRNTH)
		return (err_msg("empty", "PARENTHESIS", EMPTY_PRNTH));
	else if (error == N_CLS_DQTS)
		return (err_msg("no clossing", "DOUBLE QUOTES", N_CLS_DQTS));
	else if (error == N_CLS_SQTS)
		return (err_msg("no clossing", "SINGLE QUOTES", N_CLS_SQTS));
	else if (error == TKN_AFT_OPN_PRNTH)
		return (parse_err(parse, str, TKN_AFT_OPN_PRNTH));
	else if (error == TKN_BFR_CLS_PRNTH)
		return (parse_err(parse, str, TKN_BFR_CLS_PRNTH));
	else if (error == BAD_OPRTR_SYNTAX)
		return (parse_err(parse->prev, str, BAD_OPRTR_SYNTAX));
	else if (error == TKN_BFR_OPN_PRNTH)
		return (parse_err(parse, str, TKN_BFR_OPN_PRNTH));
	else if (error == TKN_AFT_CLS_PRNTH)
		return (parse_err(parse, str, TKN_AFT_CLS_PRNTH));
	return (0);
}

static int	err_msg(char *msg1, char *msg2, t_sytx_er error)
{
	printf("Syntax ERROR, %s %s\n", msg1, msg2);
	return (error);
}

static char	*token_name(t_parse *parse, char *str)
{
	int		index;
	char	*token;

	index = 0;
	token = malloc((parse->size + 1) * sizeof(char));
	while (index < parse->size)
	{
		token[index] = str[parse->start + index];
		index++;
	}
	token[index] = '\0';
	return (token);
}

static int	parse_err(t_parse *parse, char *str, t_sytx_er error)
{
	char	*token;
	int		flag;

	token = "??";
	flag = 0;
	if (parse->type == PIPE)
		token = "|";
	else if (parse->type == AND_OP)
		token = "||";
	else if (parse->type == OR_OP)
		token = "&&";
	else if (parse->type == OPEN_PAREN)
	{
		if (error == TKN_BFR_OPN_PRNTH)
			token = ")";
		else
			token = "(";
	}
	else if (parse->type == REDI_IN)
		token = "<";
	else if (parse->type == REDI_OUT)
		token = ">";
	else if (parse->type == HERE_DOC)
		token = "<<";
	else if (parse->type == APPEND)
		token = ">>";
	else if (parse->type & (COMMAND | D_QUOTES | S_QUOTES))
	{
		if (error == TKN_AFT_CLS_PRNTH)
			token = ")";
		if (error == TKN_BFR_OPN_PRNTH)
		{
			token = token_name(parse, str);
			flag = 1;
		}
	}
	printf("syntax error near unexpected token, '%s'\n", token);
	if (flag)
		free(token);
	return (error);
}
