/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:42:48 by tforster          #+#    #+#             */
/*   Updated: 2024/05/12 16:43:21 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tabs(int len)
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

void	print_parenth(t_parse *parse, int len)
{
	t_parse	*print;
	int		sub_len;

	print = parse;
	while (print)
	{
		if (len > 0)
			print_tabs(len);
		else
			printf("\n---");
		printf("[");
		show_str_type(print->type);
		printf("] ");
		printf("START[%d] LEN[%d]", print->start, print->size);
		printf(" [END]\n");
		if (print->sub)
		{
			// printf("|\n");
			sub_len = len + 1;
			print_parenth(print->sub, sub_len);
		}
		print = print->next;
	}
}
