/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:43:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/01 17:29:10 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

int main()
{
	t_var_minishell var;
	t_lst	*t;

	var.matrix_lst = ft_init_matrix();
	var.input_user = ft_init_lst();
	var.infile = readline("minishell ~:");
	ft_add_string_in_list(var.input_user, var.infile);
	ft_scanner_input(var.input_user);
	if (ft_have_operator(var.input_user))
	{
		if (ft_separate_operators(var.matrix_lst, var.input_user))
			printf("aqui um erro");
	}
	else
	{
		ft_add_list_front(var.matrix_lst, var.input_user);
	}
	ft_print_matrix_line(var.matrix_lst);
	ft_expander_variable(var.matrix_lst);
	ft_print_matrix_line(var.matrix_lst);
	//ft_delete_list(var.input_user);
	//free(var.infile);
}

