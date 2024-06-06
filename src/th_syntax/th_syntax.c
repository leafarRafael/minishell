/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:47:17 by tforster          #+#    #+#             */
/*   Updated: 2024/06/06 18:12:09 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "th_parser.h"
#include "th_syntax.h"

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
	if (parse)
		parse_free(parse);
	else
		return (1);
	if (status)
		return (1);
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
