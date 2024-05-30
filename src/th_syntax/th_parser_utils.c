/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:48:36 by tforster          #+#    #+#             */
/*   Updated: 2024/05/30 16:42:48 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"

int	th_is_tab(int ch)
{
	if ((7 <= ch && ch <= 13) || ch == ' ')
		return (1);
	return (0);
}

int	th_is_in_set(char ch, char *set)
{
	while (*set)
	{
		if (ch == *(set++))
			return (1);
	}
	return (0);
}

int	th_is_quote(char *str, int index)
{
	int	result;

	result = 0;
	result += (str[index] == '\"') * D_QUOTES;
	result += (str[index] == '\'') * S_QUOTES;
	return (result);
}

int	th_is_logical_oprtr(char *str, int index)
{
	int	result;

	result = 0;
	result += (str[index] == '|' && str[index + 1] != '|') * PIPE;
	result += (str[index] == '|' && str[index + 1] == '|') * AND_OP;
	result += (str[index] == '&' && str[index + 1] == '&') * OR_OP;
	return (result);
}

int	th_is_io_rdrct(char *str, int index)
{
	int	result;

	result = 0;
	result += (str[index] == '<' && str[index + 1] != '<') * REDI_IN;
	result += (str[index] == '>' && str[index + 1] != '>') * REDI_OUT;
	result += (str[index] == '<' && str[index + 1] == '<') * HERE_DOC;
	result += (str[index] == '>' && str[index + 1] == '>') * APPEND;
	return (result);
}
