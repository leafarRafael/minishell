/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:46:00 by tforster          #+#    #+#             */
/*   Updated: 2024/05/15 15:48:57 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err_msg(char *msg1, char *msg2, t_sytx_er error);

// remove the t_parse parse from the function
int	th_syntax_error(t_parse *parse, t_sytx_er error)
{
	if (error == N_CLS_PRNTH)
		return (err_msg("no clossing", "PARENTHESIS", N_CLS_PRNTH));
	else if (error == N_OPN_PRNTH)
		return (err_msg("no opennig", "PARENTHESIS", N_OPN_PRNTH));
	else if (error == N_CLS_DQTS)
		return (err_msg("no clossing", "DOUBLE QUOTES", N_CLS_DQTS));
	else if (error == N_CLS_SQTS)
		return (err_msg("no clossing", "SINGLE QUOTES", N_CLS_SQTS));
	else if (error == BAD_OPRTR_SYNTAX)
		return (err_msg("invalid", "OPERATOR", BAD_OPRTR_SYNTAX));
	else if (error == SYNTAX_ERROR)
		return (err_msg("single &", "OPERATOR", SYNTAX_ERROR));
	return (0);
}

static int	err_msg(char *msg1, char *msg2, t_sytx_er error)
{
	printf("Syntax ERROR, %s %s\n", msg1, msg2);
	return (error);
}
