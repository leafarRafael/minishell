/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/05/22 20:00:21 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_parser.h"
#include "th_syntax.h"

static int	parse_prnth(char *str, t_parse **parse, int *index);
int append_sub(char *str, t_parse *parse, int *index, t_parse_func func);

t_parse	*th_parse_param(char *str)
{
	t_parse	*parse;
	// t_parse	*parse_array;
	int		index;
	size_t	len;
	int		status;

	status = 0;
	len = ft_strlen(str);
	// printf("READLINE LEN = [%zu]\n", len);
	// parse_array = malloc((len + 1) * sizeof(t_parse));
	parse = NULL;
	index = 0;
	while (str[index])
	{
		// printf("BASE index[%d] [%c]\n", index, str[index]);
		if (th_is_tab(str[index]))
			index++;
		else if (str[index] == ')')
			status = th_syntax_error(parse, N_OPN_PRNTH);
		else if (str[index] == '(')
			status = parse_prnth(str, &parse, &index);
		else if (th_is_quote(str, index))
			status = parse_quote(str, &parse, &index);
		else if (th_is_logical_oprtr(str, index))
			status = parse_oprtr(str, &parse, &index);
		else if (th_is_io_rdrct(str, index))
			status = parse_rdrct(str, &parse, &index);
		else
			status = parse_text(str, &parse, &index);
		if (status > 0)
		{
			break ;
			// parse_free(parse);
			// return (NULL);
		}
	}
	// index = -1;
	// status = parse_prnth(str, &parse, &index);

	printf("\n");
	printf("PARSER RESULT:\n");
	th_print_parenth(str, parse, 0);
	// printf("RESULT\n");
	// printf("SIZE = [%d]\n", parse->size);
	// printf("SIZE = [%d]\n", parse->next->size);
	// printf("SIZE = [%d]\n", parse->next->prev->size);

	return (parse);
}

static int	parse_prnth(char *str, t_parse **parse, int *index)
{
	t_parse				*ptr;
	int					status;

	status = 0;
	ptr = parse_add_back(parse, parse_new(OPEN_PAREN, *index + 1));
	// ptr = parse_add_back(parse, parse_new(COMMAND, *index + 1));
	while (str[(*index)++])
	// while (str[++(*index)])
	{
		// printf("PARENTH index[%d] [%c]\n", *index, str[*index]);
		if (th_is_tab(str[*index]))
			ptr->size++;
		else if (str[*index] == '(')
			status  = append_sub(str, ptr, index, parse_prnth);
		else if (str[*index] == '\0')
		// CAHNGE TO STATUS TO PRINT THE ERROR IN THE END!!!
			return (th_syntax_error(*parse, N_CLS_PRNTH));
		else if (str[*index] == ')')
		{
			(*index)++;
			break ;
		}
		else if (th_is_quote(str, *index))
			status  = append_sub(str, ptr, index, parse_quote);
		else if (th_is_logical_oprtr(str, *index))
			status  = append_sub(str, ptr, index, parse_oprtr);
		else if (th_is_io_rdrct(str, *index))
			status  = append_sub(str, ptr, index, parse_rdrct);
		// else if (str[*index] == '\0')
		// 	break;
		else
			status  = append_sub(str, ptr, index, parse_text);
		if (status > 0)
		// MOVE ALL ERROR MESSAGES TO HERE!!!!!!
			return (status);
	}
	return (status);
}

// MOVE THIS TO THE PASER.H
int append_sub(char *str, t_parse *parse, int *index, t_parse_func func)
{
	t_parse	*sub;
	t_parse	*last;
	int		status;
	int		size;

	// sub = NULL;
	status = func(str, &parse->sub, index);
	// if (status > 0)
	// 	return (status);
	(*index)--;
	// last = parse_add_back(&parse->sub, sub);
	last = parse_last(parse->sub);
	size = 2 * ((last->type & (OPEN_PAREN | D_QUOTES | S_QUOTES)) > 0);
	parse->size += size + last->size;
	// if (parse->type == OPEN_PAREN && (parse->sub->type & (PIPE | AND_OP | OR_OP)))
	if (parse->type == OPEN_PAREN && token_is_oprtr(parse->sub))
		// return (th_syntax_error(parse, 1));
		return (th_syntax_error(parse, BAD_PRNTH_SYNTAX));
	return (status);

	// sub = NULL;
	// status = func(str, &sub, index);
	// // if (status > 0)
	// // 	return (status);
	// (*index)--;
	// last = parse_add_back(&parse->sub, sub);
	// size = 2 * ((sub->type & (OPEN_PAREN | D_QUOTES | S_QUOTES)) > 0);
	// parse->size += size + last->size;


	return (status);
}


/*
()'1'"12"
01234567
|__\///
\
 \

((cmd1"lixo" arg1" arg2)&&(cmdA&&cmdB)||(cmd2|cmd3 arg3))
012345678901234567

(cmd1&|||&&&cmd2)

cmd&&&cmd&&|(cmd&||(cmd|||(cmd||&(cmd|&&(cmd&|&(cmd|&|cmd))))))

// syntax error near unexpected token `||'

<<eof cmd "arg" arg"1" "arg"2 || (cmd && (cmd | cmd > file ))

cmd1 -l -f || cmd2 't' 'y' | (cmd3 -l && cmd4 arg1 arg2 "lixo ()")

TEST OF QUOTES AND TEXT TOGHTER
"cmd1"cmd2"cmd3" cmd1"cmd2"cmd3

 */

/* TEST THIS */
/*
"cmd"cmd"cmd"
"cmd""cmd
 */


// && ( | ( && ( || && ))) NEW TEST
