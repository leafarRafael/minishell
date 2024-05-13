/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:42:48 by tforster          #+#    #+#             */
/*   Updated: 2024/05/12 21:51:31 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	th_print_tabs(int len);
static void	print_str_from_to(char *str, t_parse *parse);

void	th_print_parenth(char *str, t_parse *parse, int len)
{
	t_parse	*print = parse;
	int		sub_len;

	while (print)
	{
		if (len > 0)
			th_print_tabs(len);
		else
			printf("\n---");
		printf("[");
		show_str_type(print->type);
		printf("] ");
		print_str_from_to(str, print);
		if (print->sub)
		{
			sub_len = len + 1;
			th_print_parenth(str, print->sub, sub_len);
		}
		print = print->next;
	}
}

static void	th_print_tabs(int len)
{
	int	len0;

	len0 = len;
	while (len--)
		printf("    ");
	printf("|\n");
	while (len0--)
		printf("    ");
	printf("|--");
}

static void	print_str_from_to(char *str, t_parse *parse)
{
	int	index = 0;
	int	len = 0;

	printf("S[%d] L[%d]  {", parse->start, parse->size);
	while (index < parse->start)
		index++;
	while (len < parse->size)
	{
		printf("%c", str[index]);
		index++;
		len++;
	}
	printf("}\n");
}
