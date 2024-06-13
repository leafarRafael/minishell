/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:46:00 by tforster          #+#    #+#             */
/*   Updated: 2024/06/13 15:49:14 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"

static int	err_msg(char *msg1, char *msg2, t_sytx_er error);
static int	parse_err(t_parse *parse, char *str, t_sytx_er error);
static char	*slct_type(t_parse *parse, t_sytx_er error, char *tkn);

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
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("Syntax ERROR, ", STDERR_FILENO);
	ft_putstr_fd(RST, STDERR_FILENO);
	ft_putstr_fd(msg1, STDERR_FILENO);
	ft_putstr_fd(", ", STDERR_FILENO);
	ft_putendl_fd(msg2, STDERR_FILENO);
	return (error);
}

static int	parse_err(t_parse *parse, char *str, t_sytx_er error)
{
	char	*tkn;
	int		flag;

	tkn = NULL;
	flag = 0;
	tkn = slct_type(parse, error, tkn);
	if (parse->type & (COMMAND | D_QUOTES | S_QUOTES))
		tkn = error_name(parse, str, error, &flag);
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("Syntax ERROR, ", STDERR_FILENO);
	ft_putstr_fd(RST, STDERR_FILENO);
	ft_putstr_fd("near unexpected token, ", STDERR_FILENO);
	ft_putendl_fd(tkn, STDERR_FILENO);
	if (flag)
		free(tkn);
	return (error);
}

static char	*slct_type(t_parse *parse, t_sytx_er error, char *tkn)
{
	if (parse->type == PIPE)
		tkn = "|";
	else if (parse->type == AND_OP)
		tkn = "||";
	else if (parse->type == OR_OP)
		tkn = "&&";
	else if (parse->type == OPEN_PAREN)
		tkn = error_opn_prnth(error);
	else if (parse->type == REDI_IN)
		tkn = "<";
	else if (parse->type == REDI_OUT)
		tkn = ">";
	else if (parse->type == HERE_DOC)
		tkn = "<<";
	else if (parse->type == APPEND)
		tkn = ">>";
	return (tkn);
}
