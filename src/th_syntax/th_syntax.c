/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/06/12 16:42:49 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_parser.h"
#include "th_syntax.h"

static void	concatenate(t_parse *parse);
static void	append_sub_text(t_parse **parse, t_parse *last, int dif);
static	int	check_wild_card(char *str, t_parse *parse);

int	last_tkn(char *str, t_parse *parse, int status)
{
	t_parse		*last;

	last = parse_last(parse);
	if (!status && parse && (tkn_is_oprtr(last) || tkn_is_rdrct(last)))
		return (syntax_error(last, str, TKN_BFR_CLS_PRNTH));
	return (status);
}

int	th_parse_param(char *str)
{
	t_parse	*parse;
	int		index;
	int		status;

	parse = NULL;
	index = 0;
	status = parse_out_prnht(str, &parse, &index);
	status = last_tkn(str, parse, status);
	concatenate(parse);
	status =  check_wild_card(str, parse);
	printf("\nPIRNT FULL\n");
	th_print_parenth(str, parse, 0, 0);
	if (parse)
		parse_free(parse);
	else
		return (1);
	if (status)
		return (1);
	return (0);
}

static void	concatenate(t_parse *parse)
{
	t_parse	*last;
	int		type;
	int		next;

	while (parse && parse->next)
	{
		last = parse_sub_last(parse);
		type = last->type;
		next = parse->next->type;
		if ((type & next) & COMMAND)
			parse = parse->next;
		else if (((type & COMMAND) && (next & (D_QUOTES | S_QUOTES)))
			|| ((type & (D_QUOTES | S_QUOTES)) && (next & COMMAND)))
			append_sub_text(&parse, last, 1);
		else if ((type & (D_QUOTES | S_QUOTES))
			&& (next & (D_QUOTES | S_QUOTES)))
			append_sub_text(&parse, last, 2);
		else
			parse = parse->next;
	}
}

static void	append_sub_text(t_parse **parse, t_parse *last, int dif)
{
	int		end;
	int		begin;
	t_parse	*pop;

	end = last->start + last->size;
	begin = (*parse)->next->start;
	if (begin - end == dif)
	{
		pop = parse_pop((*parse)->next);
		last->sub = pop;
	}
	else
		*parse = (*parse)->next;
}

static	int	check_wild_card(char *str, t_parse *parse)
{
	while (parse)
	{
		if (parse->type & (REDI_IN | REDI_OUT | APPEND))
		{
			t_parse	*sub_text;

			sub_text = parse->next;
			while (sub_text)
			{
				if (sub_text->type & COMMAND)
				{
					while (sub_text->size-- > 0)
					{
						if (str[sub_text->start] == '*')
						{
							printf("WILDCARD ERROR\n");
							return (1);
						}
					}
				}
				sub_text = sub_text->sub;
			}
		}
		parse = parse->next;
	}
	return (0);
}


/*
()'1'"12"
((cmd1"lixo" arg1" arg2)&&(cmdA&&cmdB)||(cmd2|cmd3 arg3))
012345678901234567
(cmd1&|||&&&cmd2)
cmd&&&cmd&&|(cmd&||(cmd|||(cmd||&(cmd|&&(cmd&|&(cmd|&|cmd))))))
<<eof cmd "arg" arg"1" "arg"2 || (cmd && (cmd | cmd > file ))
cmd1 -l -f || cmd2 't' 'y' | (cmd3 -l && cmd4 arg1 arg2 "lixo ()")
"cmd1"cmd2"cmd3" cmd1"cmd2"cmd3
(cmd&& (cmd |c,d)  && cd) || cmd >> file || (cmd || cmd || (cmd))
"cmd"cmd"cmd"
"cmd""cmd
&& ( | ( && ( || && ))) NEW TEST
THIS WORKS
( ls || )
NOT
( || ls )
( cmd || << || )
(>> file (cdm ) || cmd >> file )
111(222(333))
11>>(22>>(33>>(cmd)))
 */

/*
|| (ls) && (ls) >>
 */
