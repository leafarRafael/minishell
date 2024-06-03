/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:26:51 by tforster          #+#    #+#             */
/*   Updated: 2024/06/03 18:13:05 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"
#include "th_syntax.h"

static int	token_afr_cls_prnth(t_parse *parse, char *str, int status);

int	parse_quote(char *str, t_parse **parse, int *index)
{
	t_parse				*ptr;
	t_type_character	type;
	t_sytx_er			error;
	char				quote;
	int					status;

	status = 0;
	type = th_is_quote(str, *index);
	error = (type == D_QUOTES) * N_CLS_DQTS + (type == S_QUOTES) * N_CLS_SQTS;
	quote = (type == D_QUOTES) * '\"' + (type == S_QUOTES) * '\'';
	ptr = parse_add_back(parse, parse_init(type, *index + 1));
	while (str[(*index)++])
	{
		if (str[*index] == '\0')
			return (syntax_error(*parse, str, error));
		else if (str[*index] == quote)
		{
			(*index)++;
			break ;
		}
		else
			ptr->size++;
	}
	return (token_afr_cls_prnth(ptr, str, status));
}

int	parse_text(char *str, t_parse **parse, int *index)
{
	t_parse	*ptr;
	int		type;
	int		status;

	status = 0;
	ptr = parse_add_back(parse, parse_init(COMMAND, *index));
	while (str[(*index)] && !th_is_in_set(str[(*index)], "|<>() \'\""))
	{
		if (str[*index] == '&' && str[*index + 1] == '&')
			break ;
		ptr->size++;
		(*index)++;
	}
	return (token_afr_cls_prnth(ptr, str, status));
}

/**
 * @brief Syntax Check:
 * @note Check if after a CLOSE PARENTHESIS ")" there is a COMMAND "text"
*/
static int	token_afr_cls_prnth(t_parse *parse, char *str, int status)
{
	if ((parse->prev && parse->prev->type == OPEN_PAREN)
		&& (parse->type & (COMMAND | D_QUOTES | S_QUOTES)))
		status = syntax_error(parse, str, TKN_AFT_CLS_PRNTH);
	return (status);
}
