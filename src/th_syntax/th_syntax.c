/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/05/27 20:57:06 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_parser.h"
#include "th_syntax.h"

int	parse_prnth(char *str, t_parse **parse, int *index);
int append_sub(char *str, t_parse *parse, int *index, t_parse_func func);

int token_bfr_cls_prnth(t_parse *parse);
int parse_cls_prnth(t_parse *parse, char *str, int *index);

// int syntax_rdrct_file(t_parse *parse);
// static int syntax_cmd_opn_prnthX(t_parse *parse, char *str, int status);
// static int syntax_rdrct_opn_prnthX(t_parse *parse, char *str, int status);


t_parse	*th_parse_param(char *str)
{
	t_parse	*parse;
	int		index;
	int		status;

	status = 0;
	parse = NULL;
	index = 0;
	while (str[index])
	{
		// printf("BASE index[%d] [%c]\n", index, str[index]);
		if (th_is_tab(str[index]))
			index++;
		else if (str[index] == ')')
			status = syntax_error(parse, str, N_OPN_PRNTH);
		else if (str[index] == '(')
			status = parse_bfr_fst_prnth(&parse, str, &index);
		else if (th_is_quote(str, index))
			status = parse_quote(str, &parse, &index);
		else if (th_is_logical_oprtr(str, index))
			status = parse_oprtr(str, &parse, &index);
		else if (th_is_io_rdrct(str, index))
			status = parse_rdrct(str, &parse, &index);
		else
			status = parse_text(str, &parse, &index);
		if (status > 0)
			break ;
	}
	// index = -1;
	// status = parse_prnth(str, &parse, &index);
	printf("\n");
	printf("PARSER RESULT:\n");
	th_print_parenth(str, parse, 0);
	return (parse);
}

int	parse_prnth(char *str, t_parse **parse, int *index)
{
	t_parse				*ptr;
	int					status;

	status = NO_ERROR;
	ptr = parse_add_back(parse, parse_new(OPEN_PAREN, *index + 1));
	while (str[(*index)++])
	{
		if (th_is_tab(str[*index]))
			ptr->size++;
		else if (str[*index] == '(')
		{
			// if (parse_bfr_sub_prnth(ptr->sub, str, index))
			// 	status = syntax_error(parse_last(ptr->sub), str, STX_IN_TOKEN);
			// else
			// 	status = append_sub(str, ptr, index, parse_prnth);

			status = parse_bfr_sub_prnth(ptr, str, index);
		}
		else if (str[*index] == '\0')
			return (syntax_error(*parse, str, N_CLS_PRNTH));
		else if (str[*index] == ')')
		{
			if (ptr->sub && (token_is_oprtr(parse_last(ptr->sub)) || token_is_rdrct(parse_last(ptr->sub))))
				return(syntax_error(parse_last(ptr->sub), str, STX_OPRTR_CLS_PRNTH));
			if (ptr->sub == NULL)
				return(syntax_error(ptr, str, EMPTY_PRNTH));
			(*index)++;
			return(status);
			// break ;
		}
		else if (th_is_quote(str, *index))
			status  = append_sub(str, ptr, index, parse_quote);
		else if (th_is_logical_oprtr(str, *index))
			status  = append_sub(str, ptr, index, parse_oprtr);
		else if (th_is_io_rdrct(str, *index))
			status  = append_sub(str, ptr, index, parse_rdrct);
		else
			status  = append_sub(str, ptr, index, parse_text);
		if (status > 0)
			return (status);
	}
	return (status);
}

// Check if after an OPERATOR "|, ||, &&" there is CLOSE PARENTHESIS ")"
// Check if after a REDIRECT  "< , >, <<, >>" there is CLOSE PARENTHESIS ")"
int token_bfr_cls_prnth(t_parse *parse)
{
	if (parse->sub && (token_is_oprtr(parse_last(parse->sub)) || token_is_rdrct(parse_last(parse->sub))))
		return (1);
	return (0);
}

// Check if there is an EMPTY PARENTHESIS "(...))"
int parse_cls_prnth(t_parse *parse, char *str, int *index)
{
	if (token_bfr_cls_prnth(parse))
		return(syntax_error(parse_last(parse->sub), str, STX_OPRTR_CLS_PRNTH));
	if (parse->sub == NULL)
		return(syntax_error(parse, str, EMPTY_PRNTH));
	(*index)++;
	return (0);
}

// Check if after a OPEN PARENTHESIS "(" there is an OPERATOR "|, ||, &&"
int token_aft_opn_prnth(t_parse *parse)
{
	if (parse->type == OPEN_PAREN && token_is_oprtr(parse->sub))
		return (1);
	return (0);
}

// Check if after a OPEN PARENTHESIS "(" there is an OPERATOR "|, ||, &&"
int syntax_opn_prnth_oprtr(t_parse *parse, char *str, int status)
{
	// printf("ERROR 00\n");
	if (parse->type == OPEN_PAREN && token_is_oprtr(parse->sub))
	{
		// printf("ERROR 01\n");
		status = syntax_error(parse, str, STX_OPN_PRNTH_OPRTR);
	}
	// printf("STATUS [%d]\n", status);
	return (status);
}


// MOVE THIS TO THE PASER.H
int append_sub(char *str, t_parse *parse, int *index, t_parse_func parse_func)
{
	t_parse	*sub;
	t_parse	*last;
	int		status;
	int		size;

	status = parse_func(str, &parse->sub, index);
	(*index)--;
	last = parse_last(parse->sub);
	size = 2 * ((last->type & (OPEN_PAREN | D_QUOTES | S_QUOTES)) > 0);
	parse->size += size + last->size;
	// return (syntax_opn_prnth_oprtr(parse, str, status));
	if (token_aft_opn_prnth(parse))
		return (syntax_error(parse, str, STX_OPN_PRNTH_OPRTR));
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
(cmd&& (cmd |c,d)  && cd) || cmd >> file || (cmd || cmd || (cmd))

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


/*
( cmd || << || )
(>> file (cdm ) || cmd >> file )
111(222(333))
11>>(22>>(33>>(cmd)))
 */
