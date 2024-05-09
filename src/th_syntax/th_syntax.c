/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/05/09 16:14:24 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_tab(int ch);
static void	parse_cmd(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	parse_prnths(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	parse_s_qts(char *str, t_parse *parse, t_parse **ptr, int *index);
static void	parse_d_qts(char *str, t_parse *parse, t_parse **ptr, int *index);

void	print_parenth(t_parse *parse)
{
	printf("\n");
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

t_parse	*th_parse_param(char *str)
{
	t_parse	*parse;
	t_parse	*ptr;
	int		index;
	size_t	len;

	len = ft_strlen(str);
	printf("READLINE LEN = [%zu]\n", len);
	// parse = malloc((len + 1) * sizeof(parse));
	parse = NULL;
	index = 0;
	while (str[index])
	{
		while (ft_is_tab(str[index]))
			index++;
		if (str[index] == '(')
		{
			parse_add_back(&parse, parse_new(OPEN_PAREN, index));
			ptr = parse_last(parse);
			while (str[index])
			{
				if (str[index++] == ')')
					break ;
				else if (str[index] == '\0')
				{
					parse_free(parse);
					printf("Syntax ERROR, no clossing [)]");
					return(parse);
				}
				else
					ptr->size++;
			}
			index++;
		}
		else if (str[index] == '\"')
		{
			parse_add_back(&parse, parse_new(D_QUOTES, index));
			ptr = parse_last(parse);
			while (str[index])
			{
				if (str[index++] == '\"')
					break ;
				else if (str[index] == '\0')
					return(parse);
				else
					ptr->size++;
			}
			index++;
		}
		else if (str[index] == '\'')
		{
			parse_add_back(&parse, parse_new(S_QUOTES, index));
			ptr = parse_last(parse);
			while (str[index])
			{
				if (str[index++] == '\'')
					break ;
				else if (str[index] == '\0')
					return(parse);
				else
					ptr->size++;
			}
			index++;
		}
		else
		{
			index++;
		}

		// if (str[index] == ')' && ptr->type == NO_OP_TYPE)
		// {
		// 	printf("SYNTAX ERROR, CLOSE PARENTHESIS BEFORE OPEN ONE\n");
		// 	return(parse);
		// }
		// else if (str[index] == ')' && ptr->type == OPEN_PAREN)
		// {
		// 	printf("CLOSE PARENTHESIS\n");
		// 	ptr->type = NO_OP_TYPE;
		// 	index++;
		// 	ptr->start++;
		// }

		// // SET STATE
		// if (str[index] == '(' && ptr->type == NO_OP_TYPE)
		// {
		// 	printf("OPEN PARENTHESIS\n");
		// 	ptr->type = OPEN_PAREN;
		// 	// index++;
		// 	ptr->start++;
		// }
		// else if (str[index] == '\'' && ptr->type == NO_OP_TYPE)
		// {
		// 	printf("OPEN SINGLE QUOTES\n");
		// 	ptr->type = S_QUOTES;
		// 	// index++;
		// 	ptr->start++;
		// }
		// else if (str[index] == '\"' && ptr->type == NO_OP_TYPE)
		// {
		// 	printf("OPEN DOUBLE QUOTES\n");
		// 	ptr->type = D_QUOTES;
		// 	// index++;
		// 	ptr->start++;
		// }
		// // END

		// // HANDLE STATE
		// if (ptr->type == S_QUOTES)
		// {
		// 	parse_s_qts(str, parse, &ptr, &index);
		// 	if (index == len && ptr->type == S_QUOTES)
		// 	{
		// 		printf("SYNTAX ERROR, NO CLOSED SINGLE QUOTES\n");
		// 		return(parse);
		// 	}
		// }
		// else if (ptr->type == D_QUOTES)
		// {
		// 	parse_d_qts(str, parse, &ptr, &index);
		// 	if (index == len && ptr->type == D_QUOTES)
		// 	{
		// 		printf("SYNTAX ERROR, NO CLOSED DOUBLE QUOTES\n");
		// 		return(parse);
		// 	}
		// }
		// else if (ptr->type == OPEN_PAREN)
		// {
		// 	parse_prnths(str, parse, &ptr, &index);
		// 	if (index == len && ptr->type == OPEN_PAREN)
		// 	{
		// 		printf("SYNTAX ERROR, NO CLOSED PARENTHESIS\n");
		// 		return(parse);
		// 	}
		// }
		// else
		// {
		// 	index++;
		// 	ptr->start++;
		// }

		// END
		// if (ptr->type == CMD && str[index])
		// 	parse_cmd(str, parse, &ptr, &index);
		// else if (ptr->type == NO_OP_TYPE && str[index])
		// 	parse_txt(str, parse, &ptr, &index);
	}
	print_parenth(parse);
	return (parse);
}

// static void	rcsv_parse(char *str, t_parse *parse, t_parse **ptr, int *index)
// {
// 	while (str[index])
// 	{
// 		while (ft_is_tab(str[index]) && ptr->type == NO_OP_TYPE)
// 		{
// 			index++;
// 			ptr->start++;
// 		}
// 		if (str[index] == ')' && ptr->type == NO_OP_TYPE)
// 		{
// 			printf("SYNTAX ERROR, CLOSE PARENTHESIS BEFORE CLOSE ONE\n");
// 			return(parse);
// 		}
// 		else if (str[index] == ')' && ptr->type == OPEN_PAREN)
// 		{
// 			printf("CLOSE PARENTHESIS\n");
// 			ptr->type = NO_OP_TYPE;
// 			index++;
// 			ptr->start++;
// 		}
// 		// SET STATE
// 		if (str[index] == '(' && ptr->type == NO_OP_TYPE)
// 		{
// 			printf("OPEN PARENTHESIS\n");
// 			ptr->type = OPEN_PAREN;
// 			// index++;
// 			ptr->start++;
// 		}
// 		else if (str[index] == '\'' && ptr->type == NO_OP_TYPE)
// 		{
// 			printf("OPEN SINGLE QUOTES\n");
// 			ptr->type = S_QUOTES;
// 			ptr->start++;
// 		}
// 		else if (str[index] == '\"' && ptr->type == NO_OP_TYPE)
// 		{
// 			printf("OPEN DOUBLE QUOTES\n");
// 			ptr->type = D_QUOTES;
// 			ptr->start++;
// 		}
// 		// END
// 		// HANDLE STATE
// 		if (ptr->type == S_QUOTES)
// 		{
// 			parse_s_qts(str, parse, &ptr, &index);
// 			if (index == len && ptr->type == S_QUOTES)
// 			{
// 				printf("SYNTAX ERROR, NO CLOSED SINGLE QUOTES\n");
// 				return(parse);
// 			}
// 		}
// 		else if (ptr->type == D_QUOTES)
// 		{
// 			parse_d_qts(str, parse, &ptr, &index);
// 			if (index == len && ptr->type == D_QUOTES)
// 			{
// 				printf("SYNTAX ERROR, NO CLOSED DOUBLE QUOTES\n");
// 				return(parse);
// 			}
// 		}
// 		else if (ptr->type == OPEN_PAREN)
// 		{
// 			parse_prnths(str, parse, &ptr, &index);
// 			if (index == len && ptr->type == OPEN_PAREN)
// 			{
// 				printf("SYNTAX ERROR, NO CLOSED PARENTHESIS\n");
// 				return(parse);
// 			}
// 		}
// 	}
// }

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
