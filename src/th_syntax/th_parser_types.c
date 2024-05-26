/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:26:51 by tforster          #+#    #+#             */
/*   Updated: 2024/05/25 19:42:41 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"
#include "th_syntax.h"

// Check if after a CLOSE PARENTHESIS ")" there is a COMMAND "text"
int syntax_cls_prnth_cmd(t_parse *parse, char *str, int status)
{
	if (parse->prev && parse->prev->type == OPEN_PAREN &&
		(parse->type & (COMMAND | D_QUOTES | S_QUOTES)))
		status = th_syntax_error(parse, str, STX_TOKEN_AFTER);
	return (status);
}

int	parse_quote(char *str, t_parse **parse, int *index)
{
	t_parse				*ptr;
	t_type_character	type;
	t_sytx_er			error;
	char				quote;
	int					status;

	// printf("START QUOTE AT index[%d] [%c]\n", *index, str[*index]);
	status = 0;
	type = th_is_quote(str, *index);
	error = (type == D_QUOTES) * N_CLS_DQTS + (type == S_QUOTES) * N_CLS_SQTS;
	quote = (type == D_QUOTES) * '\"' + (type == S_QUOTES) * '\'';
	parse_add_back(parse, parse_new(type, *index + 1));
	ptr = parse_last(*parse);
	while (str[(*index)++])
	{
		// printf("QUOTE index[%d] [%c]\n", *index, str[*index]);
		if (str[*index] == '\0')
			return (th_syntax_error(*parse, str, error));
		else if (str[*index] == quote)
		{
			(*index)++;
			break ;
		}
		else
			ptr->size++;
	}
	return (syntax_cls_prnth_cmd(ptr, str, status));
}

int	parse_text(char *str, t_parse **parse, int *index)
{
	t_parse	*ptr;
	int		type;
	int		status;

	// printf("START TEXT AT index[%d] [%c]\n", *index, str[*index]);
	status = 0;
	parse_add_back(parse, parse_new(COMMAND, *index));
	ptr = parse_last(*parse);
	while (str[(*index)] && !th_is_in_set(str[(*index)], "|<>() \'\""))
	{
		// printf("TXT index[%d] [%c]\n", *index, str[*index]);
		if (str[*index] == '&' && str[*index + 1] == '&')
			break ;
		ptr->size++;
		(*index)++;
	}
	// return (status);
	return (syntax_cls_prnth_cmd(ptr, str, status));
}
