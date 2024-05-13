/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/05/12 21:50:21 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_prnth(char *str, t_parse **parse, int *index);
static int	parse_quote(char *str, t_parse **parse, int *index, char quote);
static int	parse_oprtr(char *str, t_parse **parse, int *index);

static void	parse_cmd(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	Xparse_prnth(char *str, t_parse *parse, t_parse **ptr, int *index);
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
			status = th_syntax_error(parse, NO_OPEN_PRNTH);
		else if (str[index] == '(')
		{
			status = parse_prnth(str, &parse, &index);
			// printf("STATUS [%d]\n", status);
		}
		else if (str[index] == '\"' || str[index] == '\'')
			status = parse_quote(str, &parse, &index, str[index]);
		else if (ft_is_in_set(str[index], "|&"))
			status = parse_oprtr(str, &parse, &index);
		else
		{
			printf("BASIC TEXT OR CMD [%d]\n", index);
			index++;
		}
		if (status > 0)
		{
			parse_free(parse);
			return (NULL);
		}
	}
	printf("\n");
	printf("RESULT\n");
	th_print_parenth(str, parse, 0);
	return (parse);
}

static int	parse_prnth(char *str, t_parse **parse, int *index)
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
			status = parse_prnth(str, &sub, index);
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
			return (th_syntax_error(*parse, NO_CLOSE_PRNTH));
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
			status = parse_oprtr(str, &sub, index);
			if (status > 0)
				return (1);
			(*index)--;
			ptr->size += parse_last(sub)->size;
			parse_add_back(&ptr->sub, sub);
		}
		else
		{
			// THIS PROBALY SHOULD GO HERE, TO TAKE ACOUNT FOR EMPTY SPACE
			// while (ft_is_tab(str[*index]))
			// 	(*index)++;
			// printf("BASIC TEXT OR CMD [%d]\n", *index);
			ptr->size++;
		}
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
	t_sytx_er			error;

	type = D_QUOTES;
	error = NO_CLOSSE_DQTS;
	if (quote =='\'')
	{
		type = S_QUOTES;
		error = NO_CLOSSE_SQTS;
	}
	parse_add_back(parse, parse_new(type, *index + 1));
	ptr = parse_last(*parse);
	while (str[(*index)++])
	{
		if (str[*index] == '\0')
			return (th_syntax_error(*parse, error));
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

static int	parse_oprtr(char *str, t_parse **parse, int *index)
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
	if (ptr->size > 2 || (ptr->size == 2 && (str[ptr->start] != str[ptr->start +1])))
		return (th_syntax_error(*parse, BAD_OPRTR_SYNTAX));
	else if (ptr->size == 1 && str[ptr->start] == '&')
		return (th_syntax_error(*parse, SYNTAX_ERROR));

	if (ptr->size == 2)
	{
		ptr->type = OR_OP;
		if (str[ptr->start] == '&' && str[ptr->start] == '&')
			ptr->type = AND_OP;
	}
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

static void	Xparse_prnth(char *str, t_parse *parse, t_parse **ptr, int *index)
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
