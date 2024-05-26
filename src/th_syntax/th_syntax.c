/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/05/25 21:22:57 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_parser.h"
#include "th_syntax.h"

static int	parse_prnth(char *str, t_parse **parse, int *index);
int append_sub(char *str, t_parse *parse, int *index, t_parse_func func);
int syntax_rdrct_file(t_parse *parse);

static int syntax_cmd_opn_prnth(t_parse *parse, char *str, int status);
static int syntax_rdrct_opn_prnth(t_parse *parse, char *str, int status);


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
			status = th_syntax_error(parse, str, N_OPN_PRNTH);
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

		// if (!status && syntax_rdrct_file(parse))
		// {
		// 	printf("==>> OPRTR ERROR IN START\n");
		// 	// show_str_type(parse_last(ptr->sub)->prev->type);
		// 	// printf("\n");
		// 	// show_str_type(parse_last(ptr->sub)->type);
		// 	// printf("\n");	// r (syntax_cls_prnth_cmd(ptr, status));

		// 	// printf("[%d]==>> IO REDIRECT ERROR\n", *index);
		// 	status = th_syntax_error(parse_last(parse), MSSNG_FILE);
		// 	printf("RDRCT ERROR [%d]\n", status);
		// }

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
	{
		// printf("PARENTH index[%d] [%c]\n", *index, str[*index]);
		if (th_is_tab(str[*index]))
			ptr->size++;
		else if (str[*index] == '(')
		{
			// MOVE THE CHECKS FROM THE RETURN, ATT THE END TO HERE!!!!!!!!
			if (ptr->prev && (ptr->prev->type & (COMMAND | D_QUOTES | S_QUOTES)))
			{
				status = th_syntax_error(ptr, str, STX_TOKEN_BEFORE);
				return (status);
			}

			status  = append_sub(str, ptr, index, parse_prnth);
		}
		else if (str[*index] == '\0')
			return (th_syntax_error(*parse, str, N_CLS_PRNTH));
		else if (str[*index] == ')')
		{
			// printf("ERROR 02\n");
			if (ptr->sub && (token_is_oprtr(parse_last(ptr->sub)) || token_is_rdrct(parse_last(ptr->sub))))
			{
				// printf("ERROR 03\n");
				return(th_syntax_error(parse_last(ptr->sub), str, STX_OPRTR_CLS_PRNTH));
			}
			if (ptr->sub == NULL)
				return(th_syntax_error(ptr, str, EMPTY_PRNTH));
			(*index)++;
			// printf("ERROR 04\n");
			// printf("STATUS [%d]\n", status);
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

		// if (syntax_rdrct_file(*parse))
		// 	return(th_syntax_error(parse_last(ptr->sub), MSSNG_FILE));
		if (status > 0)
			return (status);
	}
	// printf("ERROR 05\n");
	// printf("STATUS [%d]\n", status);

	return (syntax_cmd_opn_prnth(ptr, str, status) || syntax_rdrct_opn_prnth(ptr, str, status));
	// return (status);
}

// Check if there is file after a IO REDIRECT "< , >, <<, >>"
int syntax_rdrct_file(t_parse *parse)
{
	t_parse	*ptr;

	ptr = parse->sub;
	return (ptr &&
		(parse_last(ptr)->prev && token_is_rdrct(parse_last(ptr)->prev)) &&
		(parse_last(ptr)->type != COMMAND));
}


// Check if after a COMMAND "text" there is a OPEN PARENTHESIS "("
static int syntax_cmd_opn_prnth(t_parse *parse, char *str, int status)
{
	if (parse->prev &&
		(parse->prev->type & (COMMAND | D_QUOTES | S_QUOTES)) &&
		parse->type == OPEN_PAREN)
		status = th_syntax_error(parse, str, STX_TOKEN_BEFORE);
	return (status);
}

// Check if after a REDIRECT  "< , >, <<, >>" there is a OPEN PARENTHESIS "("
static int syntax_rdrct_opn_prnth(t_parse *parse, char *str, int status)
{
	if (parse->prev &&
		(parse->prev->type & (REDI_IN | REDI_OUT | HERE_DOC | APPEND)) &&
		parse->type == OPEN_PAREN)
		status = th_syntax_error(parse, str, STX_TOKEN_BEFORE);
	return (status);
}

// Check if after a CLOSE PARENTHESIS ")" there is a OPEN PARENTHESIS "("
int sysntax_prnth_opn_prnth(t_parse *parse, int status)
{
	return (0);
}

// Check if after a OPEN PARENTHESIS "(" there is an OPERATOR "|, ||, &&"
int syntax_opn_prnth_oprtr(t_parse *parse, char *str, int status)
{
	// printf("ERROR 00\n");
	if (parse->type == OPEN_PAREN && token_is_oprtr(parse->sub))
	{
		// printf("ERROR 01\n");
		status = th_syntax_error(parse, str, STX_OPN_PRNTH_OPRTR);
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
	return (syntax_opn_prnth_oprtr(parse, str, status));
	// return (status);
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


/*
( cmd || << || )
(>> file (cdm ) || cmd >> file )
111(222(333))
11>>(22>>(33>>(cmd)))
 */
