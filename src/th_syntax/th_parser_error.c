/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:46:00 by tforster          #+#    #+#             */
/*   Updated: 2024/05/12 21:19:04 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err_msg(char *msg1, char *msg2, t_sytx_er error);

// remove the t_parse parse from the function
int	th_syntax_error(t_parse *parse, t_sytx_er error)
{
	if (error == NO_CLOSE_PRNTH)
		return (err_msg("no clossing", "PARENTHESIS", NO_CLOSE_PRNTH));
	else if (error == NO_OPEN_PRNTH)
		return (err_msg("no opennig", "PARENTHESIS", NO_OPEN_PRNTH));
	else if (error == NO_CLOSSE_DQTS)
		return (err_msg("no clossing", "DOUBLE QUOTES", NO_CLOSSE_DQTS));
	else if (error == NO_CLOSSE_SQTS)
		return (err_msg("no clossing", "SINGLE QUOTES", NO_CLOSSE_SQTS));
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
