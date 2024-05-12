/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/05/12 19:28:05 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_prnths(char *str, t_parse **parse, int *index);
static int	parse_quote(char *str, t_parse **parse, int *index, char quote);
static int	parse_oprt(char *str, t_parse **parse, int *index);

static void	parse_cmd(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	Xparse_prnths(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	parse_s_qts(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	parse_d_qts(char *str, t_parse *parse, t_parse **ptr, int *index);

t_parse	*th_parse_param(char *str)
{
	t_parse	*parse;
	int		index;
	size_t	len;
	int		status;

	status = 0;
	len = ft_strlen(str);
	// printf("READLINE LEN = [%zu]\n", len);
	// parse = malloc((len + 1) * sizeof(parse));
	parse = NULL;
	index = 0;
	while (str[index])
	{
		printf("BASE index[%d] [%c]\n", index, str[index]);
		while (ft_is_tab(str[index]))
			index++;
		if (str[index] == ')')
			status = syntax_error(parse, ')');
		else if (str[index] == '(')
		{
			status = parse_prnths(str, &parse, &index);
			// printf("STATUS [%d]\n", status);
		}
		else if (str[index] == '\"' || str[index] == '\'')
			status = parse_quote(str, &parse, &index, str[index]);
		else if (ft_is_in_set(str[index], "|&"))
			status = parse_oprt(str, &parse, &index);
		else
			index++;
		if (status > 0)
		{
			printf("STATUS [%d]\n", status);
			return (NULL);
		}
	}
	printf("\n");
	printf("RESULT\n");
	print_parenth(parse, 0);
	return (parse);
}

static int	parse_prnths(char *str, t_parse **parse, int *index)
{
	t_parse				*ptr;
	t_parse				*sub;
	t_type_character	type;
	int					status;

	status = 0;
	parse_add_back(parse, parse_new(OPEN_PAREN, *index + 1));
	ptr = parse_last(*parse);
	while (str[(*index)++])
	{
		// printf("PARENTH index[%d] [%c]\n", *index, str[*index]);
		if (str[*index] == '(')
		{
			sub = NULL;
			status = parse_prnths(str, &sub, index);
			// printf("STATUS [%d]\n", status);
			if (status > 0)
				return (status);
			(*index)--;
			ptr->size += 2 + parse_last(sub)->size;
			parse_add_back(&ptr->sub, sub);
		}
		else if (str[*index] == '\"' || str[*index] == '\'')
		{
			// printf("%d[%c]  ", *index, str[*index]);
			sub = NULL;
			// printf("\n00 CHECK QUOTES\n");
			status = parse_quote(str, &sub, index, str[*index]);
			// printf("01\n");
			if (status > 0)
				return (status);
			(*index)--;
			// printf("02\n");
			ptr->size += 2 + parse_last(sub)->size;
			// printf("03 %d[%c]\n",  *index, str[*index]);
			parse_add_back(&ptr->sub, sub);
		}
		else if (str[*index] == '\0')
		{
			return (syntax_error(*parse, '('));
		}
		else if (str[*index] == ')')
		{
			// printf("05 BREAK %d[%c]\n",  *index, str[*index]);
			(*index)++;
			break ;
		}
		else if (ft_is_in_set(str[*index], "|&"))
		{
			sub = NULL;
			status = parse_oprt(str, &sub, index);
			if (status > 0)
				return (1);
			(*index)--;
			ptr->size += parse_last(sub)->size;
			parse_add_back(&ptr->sub, sub);
		}
		else
			ptr->size++;
		if (status > 0)
			return (status);
		// printf("04 %d[%c]\n",  *index, str[*index]);(|"&")'|||&&&' ||&&
	}
	// printf("06 INDEX: %d\n",  *index);
	return (0);
}

static int	parse_quote(char *str, t_parse **parse, int *index, char quote)
{
	t_parse				*ptr;
	t_type_character	type;

	type = D_QUOTES;
	if (quote =='\'')
		type = S_QUOTES;
	parse_add_back(parse, parse_new(type, *index + 1));
	ptr = parse_last(*parse);
	while (str[(*index)++])
	{
		if (str[*index] == '\0')
			return (syntax_error(*parse, quote));
		else if (str[*index] == quote)
		{
			(*index)++;
			break ;
		}
		else
			ptr->size++;
	}
	return (0);
}

static int	parse_oprt(char *str, t_parse **parse, int *index)
{
	t_parse	*ptr;
	int		type;

	parse_add_back(parse, parse_new(PIPE, *index));
	ptr = parse_last(*parse);
	while (str[(*index)] && ft_is_in_set(str[(*index)], "|&"))
	{
		ptr->size++;
		(*index)++;
	}
	// printf("OPTR LEN = %d\n", ptr->size);
	if (ptr->size > 2)
	{
		printf("OPTR TOO BIG\n");
		// return (-1);
	}
	else if (ptr->size == 1 && str[ptr->start] == '&')
	{
		printf("& ALONE NOT OPTR\n");
		// return (-1);
	}
	else if (ptr->size == 2 && (str[ptr->start] != str[ptr->start +1]))
	{
		printf("DIFF OPTRs\n");
		// return (-1);
	}
	// if (str[*index])
	// 	(*index)--;
	// printf("OPRT index[%d] [%c]\n", *index, str[*index]);
	return (0);
}



static void	parse_cmd(char *str, t_parse *parse, t_parse **ptr, int *index)
{
	(*ptr)->size++;
	if (ft_is_tab(str[++(*index)]))
	{
		parse_add_back(&parse, parse_new(NO_OP_TYPE, ++(*index)));
		*ptr = parse_last(parse);
	}
}

static void	Xparse_prnths(char *str, t_parse *parse, t_parse **ptr, int *index)
{
	(*ptr)->size++;
	(*index)++;
	if (str[*index] == ')')
	{
		(*ptr)->size--;
		parse->close = 1;
		// if (ft_is_tab(str[++(*index)]))
		// {
			parse_add_back(&parse, parse_new(NO_OP_TYPE, ++(*index)));
			*ptr = parse_last(parse);
			printf("CLOSED PARENTHESIS\n");

		// }
	}
}

static void	parse_s_qts(char *str, t_parse *parse, t_parse **ptr, int *index)
{
	(*ptr)->size++;
	(*index)++;
	if (str[*index] == '\'')
	{
		(*ptr)->size--;
		parse->close = 1;
		// if (ft_is_tab(str[++(*index)]))
		// {
			parse_add_back(&parse, parse_new(NO_OP_TYPE, ++(*index)));
			*ptr = parse_last(parse);
			printf("CLOSED SINGLE QUOTES\n");

		// }
	}
}

static void	parse_d_qts(char *str, t_parse *parse, t_parse **ptr, int *index)
{
	(*ptr)->size++;
	// (*index)++;
	if (str[*index] == '\"')
	{
		(*ptr)->size--;
		parse->close = 1;
		// if (ft_is_tab(str[++(*index)]))
		// {
			parse_add_back(&parse, parse_new(NO_OP_TYPE, ++(*index)));
			*ptr = parse_last(parse);
			printf("CLOSED DOUBLE QUOTES\n");

		// }
	}
}

/*
()'1'"12"
01234567
|__\///
\
 \
 */
