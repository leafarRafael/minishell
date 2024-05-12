/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/05/11 21:15:02 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_tab(int ch);
static int	check_prnths(char *str, t_parse **parse, int *index);
static int	check_quote(char *str, t_parse **parse, int *index, char quote);
static void	parse_cmd(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	parse_prnths(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	parse_s_qts(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	parse_d_qts(char *str, t_parse *parse, t_parse **ptr, int *index);

void	print_tabs(int len)
{
	int	len0;

	len0 = len;
	while (len--)
		printf("    ");
	printf("|\n");
	while (len0--)
		printf("    ");
	printf("|--");
}

void	print_parenth(t_parse *parse, int len)
{
	t_parse	*print;
	int		sub_len;

	print = parse;
	while (print)
	{
		if (len > 0)
			print_tabs(len);
		else
			printf("\n---");
		printf("[");
		show_str_type(print->type);
		printf("] ");
		printf("START[%d] LEN[%d]", print->start, print->size);
		printf(" [END]\n");
		if (print->sub)
		{
			// printf("|\n");
			sub_len = len + 1;
			print_parenth(print->sub, sub_len);
		}
		print = print->next;
	}
}

int	syntax_error(t_parse *parse, char quote)
{
	char	*msg[2];

	msg[0] = "clossing";
	msg[1] = "PARENTHESIS";
	if (quote == ')')
		msg[0] = "opennig";
	else if (quote == '\"')
		msg[1] = "DOUBLE QUOTES";
	else if (quote == '\'')
		msg[1] = "SINGLE QUOTES";
	parse_free(parse);
	printf("Syntax ERROR, no %s %s\n", msg[0], msg[1]);
	return (-1);
}

t_parse	*th_parse_param(char *str)
{
	t_parse	*parse;
	int		index;
	size_t	len;
	int		status;

	status = 1;
	len = ft_strlen(str);
	printf("READLINE LEN = [%zu]\n", len);
	// parse = malloc((len + 1) * sizeof(parse));
	parse = NULL;
	index = 0;
	while (str[index])
	{
		while (ft_is_tab(str[index]))
			index++;
		if (status && str[index] == ')')
			status = syntax_error(parse, ')');
		else if (status && str[index] == '(')
			status = check_prnths(str, &parse, &index);
		else if (status && (str[index] == '\"' || str[index] == '\''))
			status = check_quote(str, &parse, &index, str[index]);
		else
			index++;
		if (status == -1)
			return (NULL);
	}
	printf("\n");
	printf("RESULT\n");
	print_parenth(parse, 0);
	return (parse);
}

static int	check_prnths(char *str, t_parse **parse, int *index)
{
	t_parse				*ptr;
	t_parse				*sub;
	t_type_character	type;
	int					status;

	status = 1;
	parse_add_back(parse, parse_new(OPEN_PAREN, *index + 1));
	ptr = parse_last(*parse);
	while (status && str[(*index)++])
	{
		if (status && str[*index] == '(')
		{
			sub = NULL;
			status = check_prnths(str, &sub, index);
			if (status == -1)
				return (-1);
			(*index)--;
			ptr->size += 2 + parse_last(sub)->size;
			parse_add_back(&ptr->sub, sub);
		}
		else if (status && str[*index] == '\"' || str[*index] == '\'')
		{
			// printf("%d[%c]  ", *index, str[*index]);
			// sub = (*parse)->sub;
			sub = NULL;
			// printf("\n00 CHECK QUOTES\n");
			status = check_quote(str, &sub, index, str[*index]);
			// printf("01\n");
			if (status == -1)
				return (-1);
			(*index)--;
			// printf("02\n");
			ptr->size += 2 + parse_last(sub)->size;
			// printf("03 %d[%c]\n",  *index, str[*index]);
			// ptr->sub = sub;
			parse_add_back(&ptr->sub, sub);
		}
		else if (status && str[*index] == '\0')
			return (syntax_error(*parse, '('));
		else if (status && str[*index] == ')')
		{
			// printf("05 BREAK %d[%c]\n",  *index, str[*index]);
			(*index)++;
			break ;
		}
		else
			ptr->size++;
		// printf("04 %d[%c]\n",  *index, str[*index]);
	}
	// printf("06 INDEX: %d\n",  *index);
	return (1);
}

static int	check_quote(char *str, t_parse **parse, int *index, char quote)
{
	t_parse				*ptr;
	t_type_character	type;

	type = S_QUOTES;
	if (quote =='\'')
		type = D_QUOTES;
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
	return (1);
}

static int	ft_is_tab(int ch)
{
	if ((7 <= ch && ch <= 13) || ch == ' ')
		return (1);
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

static void	parse_prnths(char *str, t_parse *parse, t_parse **ptr, int *index)
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
