/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/24 15:58:07 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_ttype();

int main()
{
	t_array_lst		*lst_array;
	t_matrix_lst	*matrix_lst;
	t_var_minishell var;

	lst_array = init_array_lst();
	matrix_lst = ft_init_matrix_lst();
	var.infile = readline("minishell ~:");
	var.i = 0;
	while (var.infile[var.i])
	{
		if (ft_create_addnode_back_alst(lst_array, var.infile[var.i]))
		{
			printf("error creation array_list");
			exit(-1);
		}
		var.i++;
	}
	printf("head = %c\n", lst_array->head->c);
	printf("last = %c\n", lst_array->last->c);
	ft_scanner_input(lst_array);
	ft_print_array_lst_content_type(lst_array);
	ft_delete_list(lst_array);
	free(var.infile);
	printf_ttype();
}


void	printf_ttype()
{
	printf("\n%d NO_OPERATOR_TYPE \n", NO_OPERATOR_TYPE);
	printf("%d SINGLE_QUOTES\n", SINGLE_QUOTES);
	printf("%d DOUBLE_QUOTES\n", DOUBLE_QUOTES);
	printf("%d WHITE_SPACE\n", WHITE_SPACE);
	printf("%d DOLLAR_SING\n", DOLLAR_SING);
	printf("%d REDI_INFILE\n", REDI_INFILE);
	printf("%d REDIRECT\n", REDIRECT);
	printf("%d HERE_DOC\n", HERE_DOC);
	printf("%d APPEND\n", APPEND);
	printf("%d PIPE\n", PIPE);
	printf("%d AND\n", AND);
	printf("%d OR\n", OR);
	printf("%d LEFT_PAREN\n", LEFT_PAREN);
	printf("%d RIGHT_PAREN\n", RIGHT_PAREN);
}