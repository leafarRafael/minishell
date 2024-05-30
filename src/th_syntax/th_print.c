/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:42:48 by tforster          #+#    #+#             */
/*   Updated: 2024/05/29 19:47:29 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "th_parser.h"

static void	th_print_tabs(t_parse *parse, int len, int more);
static void	print_str_from_to(char *str, t_parse *parse);

void	th_print_parenth(char *str, t_parse *parse, int len, int more)
{
	t_parse	*print = parse;
	int		sub_len;

	while (print)
	{
		if (len > 0)
			th_print_tabs(parse, len, 0);
		show_str_type(print->type);
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
		if (len == 1 || more)
		{
			printf(BLU "\u2502  " RST);
		}
		else
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
