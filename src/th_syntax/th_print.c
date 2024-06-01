/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:42:48 by tforster          #+#    #+#             */
/*   Updated: 2024/05/31 22:41:22 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"

static void	th_print_tabs(t_parse *parse, int len, int more);
static void	print_str_from_to(char *str, t_parse *parse);

void	print_type(char *str, int len)
{
	printf(BLU "[");
	len--;
	len -= ft_strlen(str) - 1;
	printf(CYN "%s", str);
	printf(BLU "]");
	len--;
	while (len--)
	{
		printf(RST " ");
	}
}

void	select_type(int type)
{
	if (type == COMMAND)
		print_type("COMMAND", 13);
	if (type == META_LITERAL)
		print_type("META_LITERAL", 13);
	if (type == NO_OP_TYPE)
		print_type("NO_OP_TYPE", 13);
	if (type == S_QUOTES)
		print_type("S_QUOTES", 13);
	if (type == D_QUOTES)
		print_type("D_QUOTES", 13);
	if (type == WH_SPACE)
		print_type("WH_SPACE", 13);
	if (type == DOLLAR)
		print_type("DOLLAR_SING", 13);
	if (type == REDI_IN)
		print_type("REDI_IN", 13);
	if (type == REDI_OUT)
		print_type("REDI_OUT", 13);
	if (type == HERE_DOC)
		print_type("HERE_DOC", 13);
	if (type == APPEND)
		print_type("APPEND", 13);
	if (type == PIPE)
		print_type("PIPE", 13);
	if (type == AND_OP)
		print_type("AND_OP", 13);
	if (type == OR_OP)
		print_type("OR_OP", 13);
	if (type == OPEN_PAREN)
		print_type("OPEN_PAREN", 13);
	if (type == CLOSE_PAREN)
		print_type("CLOSE_PAREN", 13);
}



void	th_print_parenth(char *str, t_parse *parse, int len, int more)
{
	t_parse	*print = parse;
	int		sub_len;

	while (print)
	{
		if (len > 0)
			th_print_tabs(parse, len, 0);
		select_type(print->type);
		print_str_from_to(str, print);
		if (print->sub)
		{
			if (print->next)
				more++;
			sub_len = len + 1;
			th_print_parenth(str, print->sub, sub_len, more);
		}
		print = print->next;
	}
}

static void	th_print_tabs(t_parse *parse, int len, int more)
{
	int	len0;

	len0 = len;
	if (len0 > 1)
	{
		while (--len0)
			printf("   ");
	}
	while (len--)
	{
			printf("   ");
	}
	printf(BLU "\u2502\u2015\u2015" RST);
}

static void	print_str_from_to(char *str, t_parse *parse)
{
	int	index = 0;
	int	len = 0;

	if (parse->type == OPEN_PAREN)
	{
		printf("%s(%s......%s)\n", YEL, RED, YEL);
		return ;
	}
	// printf("S[%d] L[%d]  {", parse->start, parse->size);
	printf(YEL "{ " RST);
	while (index < parse->start)
		index++;
	while (len < parse->size)
	{
		printf(RED "%c", str[index]);
		index++;
		len++;
	}
	printf(YEL " }\n" RST);
}
