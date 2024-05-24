/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_parser_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:26:51 by tforster          #+#    #+#             */
/*   Updated: 2024/05/23 20:06:21 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"
#include "th_syntax.h"

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
			return (th_syntax_error(*parse, error));
		else if (str[*index] == quote)
		{
			(*index)++;
			// if (str[*index] && !th_is_io_rdrct(str, *index) && !th_is_logical_oprtr(str, *index) && !th_is_in_set(str[*index], "() "))
			// {
			// 	// printf("QUOTES LEN [%d]\n", (*parse)->size);
			// 	status = append_sub(str, ptr, index, parse_text);
			// 	ptr->size -= parse_last(ptr)->sub->size;
			// 	// printf("QUOTES LEN AFTER APPEND [%d]\n", (*parse)->size);
			// }
			break ;
		}
		else
			ptr->size++;
	}

	return (status);
	// return (0);
}

int	token_is_oprtr(t_parse *parse)
{
	if (parse->type & (PIPE | AND_OP | OR_OP))
		return (1);
	return (0);
}

int	compare_token(t_parse *parse)
{
	if (token_is_oprtr(parse->prev))
	{
		if (token_is_oprtr(parse))
		{
			printf("==>> SYNTAX ERROR\n");
			return (th_syntax_error(parse, BAD_OPRTR_SYNTAX));
		}
	}
	return (NO_ERROR);
}

int	syntax_oprtr(t_parse *parse)
{
	if (parse->prev && token_is_oprtr(parse->prev) && token_is_oprtr(parse))
	{
		printf("==>> SYNTAX ERROR\n");
		return (th_syntax_error(parse, BAD_OPRTR_SYNTAX));
	}
	return (NO_ERROR);
}

int	parse_oprtr(char *str, t_parse **parse, int *index)
{
	t_parse	*ptr;
	int		type;

	printf("==>> IN PARSE OPERATOR\n");
	type = th_is_logical_oprtr(str, *index);
	ptr = parse_add_back(parse, parse_new(type, *index));
	// ptr = parse_last(*parse);
	ptr->size = 1;
	(*index)++;
	if (type & (OR_OP | AND_OP))
	{
		ptr->size++;
		(*index)++;
	}
	return(syntax_oprtr(ptr));
	// if (ptr->prev)
	// 	return (compare_token(ptr));
	// return (NO_ERROR);
}

int	token_is_rdrct(t_parse *parse)
{
	if (parse->type & (REDI_IN | REDI_OUT | HERE_DOC | APPEND))
		return (1);
	return (0);
}

int	syntax_rdrct(t_parse *parse)
{
	if (parse->prev && token_is_rdrct(parse->prev) && token_is_rdrct(parse))
	{
		printf("==>> SYNTAX ERROR\n");
		return (th_syntax_error(parse, BAD_RDRTC_SYNTAX));
	}
	return (NO_ERROR);
}


int	parse_rdrct(char *str, t_parse **parse, int *index)
{
	t_parse	*ptr;
	int		type;

	type = th_is_io_rdrct(str, *index);
	parse_add_back(parse, parse_new(type, *index));
	ptr = parse_last(*parse);
	ptr->size = 1;
	(*index)++;
	if (type & (HERE_DOC |  APPEND))
	{
		ptr->size++;
		(*index)++;
	}
	return (syntax_rdrct(ptr));
	// return (NO_ERROR);
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
		// if (th_is_quote(str, *index))
		// {
		// 	status = append_sub(str, ptr, index, parse_quote);
		// 	(*index)++;
		// }
		ptr->size++;
		(*index)++;
	}
	return (status);
}
