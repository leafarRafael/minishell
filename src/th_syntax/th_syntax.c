/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/05/23 21:58:28 by tforster         ###   ########.fr       */
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
			return (th_syntax_error(*parse, N_CLS_PRNTH));
		else if (str[*index] == ')')
		{
			// printf("==>> CHECK CLOSSE PARENTH ERROR\n");
			if (ptr->sub && (token_is_oprtr(parse_last(ptr->sub)) || token_is_rdrct(parse_last(ptr->sub))))
			{
				// printf("ERRO 00\n");
				// show_str_type(ptr->sub->type);
				// printf("\n");
				return(th_syntax_error(parse_last(ptr->sub), BAD_C_PRNTH_STX));
			}
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

		if (ptr->sub && (parse_last(ptr->sub)->prev && token_is_rdrct(parse_last(ptr->sub)->prev) && (parse_last(ptr->sub)->type != COMMAND)))
		{
			printf("==>> OPRTR ERROR\n");
			show_str_type(parse_last(ptr->sub)->prev->type);
			printf("\n");
			show_str_type(parse_last(ptr->sub)->type);
			printf("\n");
			printf("[%d]==>> IO REDIRECT ERROR\n", *index);
			return(th_syntax_error(parse_last(ptr->sub), MSSNG_FILE));
		}
		if (status > 0)
			return (status);
	}
	return (status);
}

// MOVE THIS TO THE PASER.H
int append_sub(char *str, t_parse *parse, int *index, t_parse_func parse_func)
{
	t_parse	*sub;
	t_parse	*last;
	int		status;
	int		size;

	// sub = NULL;
	status = parse_func(str, &parse->sub, index);
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
		return (th_syntax_error(parse, BAD_O_PRNTH_STX));
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

/*
THIS WORKS
( ls || )
NOT
( || ls )
 */
