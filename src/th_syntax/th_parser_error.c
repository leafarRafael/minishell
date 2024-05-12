/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:46:00 by tforster          #+#    #+#             */
/*   Updated: 2024/05/12 19:07:21 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_parse *parse, char quote)
{
	char	*msg[2];

	msg[0] = "clossing";
	msg[1] = "PARENTHESIS";
	if (quote == '(')
	{
		printf("Syntax ERROR, no %s %s\n", msg[0], msg[1]);
		parse_free(parse);
		return (NO_CLOSSINSG_PARENTH);
	}
	else if (quote == ')')
	{
		msg[0] = "opennig";
		printf("Syntax ERROR, no %s %s\n", msg[0], msg[1]);
		parse_free(parse);
		return (NO_OPENING_PARENTH);
	}
	else if (quote == '\"')
	{
		msg[1] = "DOUBLE QUOTES";
		printf("Syntax ERROR, no %s %s\n", msg[0], msg[1]);
		parse_free(parse);
		return (NO_CLOSSINSG_D_QUOTES);
	}
	else if (quote == '\'')
	{
		msg[1] = "SINGLE QUOTES";
		printf("Syntax ERROR, no %s %s\n", msg[0], msg[1]);
		parse_free(parse);
		return (NO_CLOSSINSG_S_QUOTES);
	}
	return (0);
}
