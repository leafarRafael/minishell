/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/05/09 20:10:07 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_tab(int ch);
static int	check_quote(char *str, t_parse **parse, int *index, char quote);
static void	parse_cmd(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	parse_prnths(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	parse_s_qts(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	parse_d_qts(char *str, t_parse *parse, t_parse **ptr, int *index);

void	print_parenth(t_parse *parse)
{
	printf("\n");
	printf("RESULT\n");
	while (parse)
	{
		printf("[");
		show_str_type(parse->type);
		printf("] ");
		printf("START[%d] LEN[%d]", parse->start, parse->size);
		printf(" [END]\n");
		parse = parse->next;
	}
}

void	syntax_error(t_parse *parse, char quote)
{
	char	*msg;

	if (quote == ')')
		msg = "PARENTHESIS";
	else if (quote == '\"')
		msg = "DOUBLE QUOTES";
	else if (quote == '\'')
		msg = "SINGLE QUOTES";
	parse_free(parse);
	printf("Syntax ERROR, no clossing %s\n", msg);
}

t_parse	*th_parse_param(char *str)
{
	t_parse	*parse;
	t_parse	*ptr;
	t_parse	*sub;
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
		if (status && str[index] == '(')
		{
			parse_add_back(&parse, parse_new(OPEN_PAREN, index + 1));
			ptr = parse_last(parse);
			while (status && str[index++])
			{
				// printf("%d[%c] ", index, str[index]);
				if (status && str[index] == '\"' || str[index] == '\'')
				{
					// if (parse->sub == NULL)
					// 	sub = parse->sub;
					// status = check_quote(str, &parse, &index, str[index]);
					status = check_quote(str, &parse->sub, &index, str[index]);
					if (status == -1)
						return (NULL);
					index--;
					// ptr->size += 2 + parse_last(parse)->size;
					ptr->size += 2 + parse_last(parse->sub)->size;
				}
				else if (status && str[index] == '\0')
				{
					syntax_error(parse, ')');
					return (NULL);
				}
				else if (status && str[index] == ')')
				{
					index++;
					break ;
				}
				else
					ptr->size++;
			}
		}
		else if (status && (str[index] == '\"' || str[index] == '\''))
			status = check_quote(str, &parse, &index, str[index]);
		else
		{
			index++;
		}
		if (status == -1)
			return (NULL);
	}
	print_parenth(parse);
	return (parse);
}

static int	check_quote(char *str, t_parse **parse, int *index, char quote)
{
	t_parse				*ptr;
	t_type_character	type;

	if (quote =='\"')
		type = S_QUOTES;
	else if (quote =='\'')
		type = D_QUOTES;
	parse_add_back(parse, parse_new(type, *index + 1));
	ptr = parse_last(*parse);
	// printf("\n");
	while (str[(*index)++])
	{
		// printf("%d[%c]", *index, str[*index]);
		if (str[*index] == '\0')
		{
			syntax_error(*parse, quote);
			return (-1);
		}
		else if (str[*index] == quote)
		{
			(*index)++;
			// printf("BREAK AT [%c]", str[*index]);
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
 */
